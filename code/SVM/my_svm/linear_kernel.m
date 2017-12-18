function [ K ] = linear_kernel( X )

n = size(X,1);
K = zeros(n);
for i = 1:n    
    for j = 1:n        
        K(i,j) = ( X(i,:) * transpose(X(j,:)) ) + 1;
    end    
end

end

