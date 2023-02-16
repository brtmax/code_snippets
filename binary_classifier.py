import torch
import torch.nn as nn
import torch.nn.functional as F
import torch.optim as optim
import torchvision.transforms as transforms
from torchvision.datasets import EMNIST
from torch.utils.data import DataLoader, random_split
from torchvision.transforms import ToTensor
from torch.utils.data import TensorDataset



# Define the transform to preprocess the data
# Define the transform to preprocess the data
transform = transforms.Compose([
    transforms.RandomRotation(degrees=10),
    transforms.RandomAffine(degrees=0, translate=(0.1, 0.1)),
    transforms.ToTensor(),
    transforms.Normalize((0.1307,), (0.3081,))
])

# Load the EMNIST dataset and select the classes of interest
# Set download to True
emnist = EMNIST(root='./data', split='balanced', download=True, transform=ToTensor())

binary_labels = torch.tensor([int(label >= 10) for label in emnist.targets])

dataset = TensorDataset(emnist.data, binary_labels)

train_size = int(0.8 * len(dataset))
test_size = len(dataset) - train_size
train_dataset, test_dataset = random_split(dataset, [train_size, test_size])

train_counts = {i: (binary_labels[train_dataset.indices] == i).sum().item() for i in range(2)}
test_counts = {i: (binary_labels[test_dataset.indices] == i).sum().item() for i in range(2)}

print(f"Class counts in train_dataset: {train_counts}")
print(f"Class counts in test_dataset: {test_counts}")

# Define the data loaders
batch_size = 64
train_loader = DataLoader(train_dataset, batch_size=batch_size, shuffle=True, drop_last=True)
test_loader = DataLoader(test_dataset, batch_size=batch_size, shuffle=True)

# Define the neural network model
class Net(nn.Module):
    def __init__(self):
        super(Net, self).__init__()

        self.conv1 = nn.Conv2d(1, 32, kernel_size=3)
        self.bn1 = nn.BatchNorm2d(32)
        self.conv2 = nn.Conv2d(32, 64, kernel_size=3)
        self.bn2 = nn.BatchNorm2d(64)
        self.conv2_drop = nn.Dropout2d()
        self.fc1 = nn.Linear(64*5*5, 128)
        self.fc2 = nn.Linear(128, 2)

    def forward(self, x):
        x = x.float()
        x = x.unsqueeze(1)
        x = self.bn1(F.leaky_relu(F.max_pool2d(self.conv1(x), 2)))
        x = self.bn2(F.leaky_relu(F.max_pool2d(self.conv2_drop(self.conv2(x)), 2)))
        x = x.view(-1, 64*5*5)
        x = F.relu(self.fc1(x))
        x = F.dropout(x, training=self.training)
        x = self.fc2(x)
        return F.log_softmax(x, dim=1)

# Initialize the model and the optimizer
model = Net()
optimizer = optim.Adam(model.parameters(), lr=0.0001)

# Define the loss function
criterion = nn.CrossEntropyLoss()

# Train the model
num_epochs = 10
for epoch in range(num_epochs):
    model.train()
    running_loss = 0.0
    for i, (inputs, labels) in enumerate(train_loader):
        optimizer.zero_grad()
        outputs = model(inputs)
        loss = criterion(outputs, labels)
        loss.backward()
        optimizer.step()
        running_loss += loss.item()

    model.eval()
    correct = 0
    total = 0
    with torch.no_grad():
        for inputs, labels in test_loader:
            outputs = model(inputs)
            _, predicted = torch.max(outputs.data, 1)
            total += labels.size(0)
            correct += (predicted == labels).sum().item()

        epoch_loss = running_loss / len(train_loader)
        epoch_accuracy = 100.0 * correct / total
        print(f"Epoch [{epoch+1}/{num_epochs}], Loss: {epoch_loss:.4f}, Accuracy: {epoch_accuracy:.2f}%")
