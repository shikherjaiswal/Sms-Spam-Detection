function [ predicted_valid_Y ] = run_svm( train_X, train_Y, valid_X )


%% Calculate kernel matrix
C = 10;
s = 0.1;
train_n = size(train_X,1);
valid_n = size(valid_X,1);

train_X_Kernel = linear_kernel(train_X);
%train_X_Kernel = quadratic_kernel(train_X);
%train_X_Kernel = gaussian_kernel(train_X, s);


%% Calculate alpha and w0
alpha = solve_dual(train_Y, train_X_Kernel, C);
w0 = solve_for_w0(alpha, train_X_Kernel, train_Y);


%% Predict values of Y for valid_X
predicted_valid_Y = zeros(valid_n,1);

for i = 1:valid_n
    x = 0;
    for j = 1:train_n
        x = x + alpha(i)*train_Y(i)*linear_dot(train_X(j,:), valid_X(i,:));
    end
    predicted_valid_Y(i) = w0 + x;
end
%%

end