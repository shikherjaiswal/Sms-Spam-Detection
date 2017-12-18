function [ w0 ] = solve_for_w0( alpha, Kernel, train_Y )

n = size(Kernel,1);
x = zeros(n,1);

for i = 1:n
    x(i) = sum(alpha.*Kernel(:,i).*train_Y);  
end
w0 = sum(train_Y-x)/n;
    
end

