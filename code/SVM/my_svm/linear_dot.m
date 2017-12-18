function [ X_dot ] = linear_dot( X1, X2 )

X_dot = (X1 * transpose(X2)) + 1;

end

