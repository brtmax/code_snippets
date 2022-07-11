double gaussian_score(double value, double mu, double sigma) {

    // This function only returns the probability density at given value
    
    
    double variance = sigma * sigma;
    
    double score = 0.0;

    double first_fraction = 1 / (sqrt(2*(M_PI) * variance));
    
    double numerator = (value - mu) * (value - mu);
    
    double denominator = 2 * (sigma * sigma);
    
    double second_fraction = -1 * (numerator / denominator);
    
    double e_raised = exp(second_fraction);

    score = first_fraction * e_raised;
    
    return score; 
}