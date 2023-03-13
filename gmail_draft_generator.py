import argparse
import csv
import os.path
from google.auth.transport.requests import Request
from google.oauth2.credentials import Credentials
from google.oauth2.credentials import Credentials as GoogleCredentials
from google_auth_oauthlib.flow import InstalledAppFlow
from googleapiclient.discovery import build
from googleapiclient.errors import HttpError
import os.path
import base64
import email
import google.auth.transport.requests
from google.oauth2.credentials import Credentials
from google_auth_oauthlib.flow import InstalledAppFlow
from googleapiclient.discovery import build
from googleapiclient.errors import HttpError
from email.mime.text import MIMEText
from email.mime.multipart import MIMEMultipart
from email.mime.base import MIMEBase
from email import encoders

#python3 gmail_draft_generator.py /home/max/Documents/repos/sources/input.csv /home/max/Documents/repos/sources/text_template.txt /home/max/Documents/repos/sources/credentials.json --vorname Max --nachname  Bretschneider

def generate_drafts(input_csv_path, text_template_path, credentials_path):
    # Load credentials
    creds = None
    if os.path.exists('token.json'):
        creds = Credentials.from_authorized_user_file('token.json', ['https://www.googleapis.com/auth/gmail.compose'])
    if not creds or not creds.valid:
        if creds and creds.expired and creds.refresh_token:
            creds.refresh(Request())
        else:
            flow = InstalledAppFlow.from_client_secrets_file(credentials_path, ['https://www.googleapis.com/auth/gmail.compose'])
            creds = flow.run_local_server(port=0)
        with open('token.json', 'w') as token:
            token.write(creds.to_json())

    # Load email template
    with open(text_template_path, 'r') as f:
        text_template = f.read()

    # Load input CSV file
    with open(input_csv_path, newline='') as csvfile:
        reader = csv.DictReader(csvfile)
        for row in reader:
            # Personalize email text
            personalized_text = text_template.replace('[VORLESUNGSNAME]', row['VORLESUNGSNAME'])
            personalized_text = personalized_text.replace('[ANREDE]', row['ANREDE'])
            personalized_text = personalized_text.replace('[TITEL]', row['TITEL'])
            personalized_text = personalized_text.replace('[DOZENT]', row['DOZENT'])
            personalized_text = personalized_text.replace('[VORNAME]', args.vorname)
            personalized_text = personalized_text.replace('[NACHNAME]', args.nachname)


            # Create draft message
            try:
                service = build('gmail', 'v1', credentials=creds)
                message = create_message(row['EMAIL'], 'KITcar Vorlesungswerbung', personalized_text)
                draft = create_draft(service, 'me', message)
                print(f"Draft created for {row['EMAIL']}")
            except HttpError as error:
                print(f'An error occurred: {error}')
                draft = None

def create_draft(service, user_id, message_body):
    message = {'message': message_body}
    draft = service.users().drafts().create(userId=user_id, body=message).execute()
    return draft

def create_message(to, subject, message_text):
    message = MIMEText(message_text)
    message['to'] = to
    message['subject'] = subject
    return {'raw': base64.urlsafe_b64encode(message.as_bytes()).decode()}

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Generate Gmail drafts from a CSV file')
    parser.add_argument('input_csv', help='Path to input CSV file')
    parser.add_argument('text_file', help='Path to text template file')
    parser.add_argument('credentials', help='Path to Google API client credentials file')
    parser.add_argument('--vorname', help='Vorname', required=True)
    parser.add_argument('--nachname', help='Nachname', required=True)
    args = parser.parse_args()
    generate_drafts(args.input_csv, args.text_file, args.credentials)
