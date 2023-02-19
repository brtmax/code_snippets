def general_preference(u, v, l, width, height):
    phi_prior = ((1 - u)**2 + (height - v)**2) / ((1 - width)**2 + (1 - height)**2)
    if l != 1:
        phi_prior = 1 - phi_prior
    return phi_prior
