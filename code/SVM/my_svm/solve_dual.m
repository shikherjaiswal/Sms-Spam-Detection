function [ alpha ] = solve_dual(train_Y, Kernel, C )


%% Set parameters for quadprog
n = size(Kernel,1);
H = ones(n);

size(H)
size(Kernel)
size(train_Y)
for i = 1:n
    H(i, :) = (H(i,:).*Kernel(i,:)).*transpose(train_Y);
    H(:, i) = (H(:,i).*Kernel(:,i)).*train_Y;
end

f = -1.*ones(n,1);
A = [];
b = [];
Aeq = transpose(train_Y);
beq = 0;
lb = zeros(n,1);
ub = C.*ones(n,1);

%% find alpha
alpha = quadprog(H, f, A, b, Aeq, beq, lb, ub);


end