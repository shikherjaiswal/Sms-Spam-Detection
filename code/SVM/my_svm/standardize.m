function [ X ] = standardize( X, X_mean, X_var )

n = size(X,2);
for i=1:n
    if X_var(i) ~= 0
        X(:,i) = (X(:,i)-X_mean(i))./X_var(i);
    end
end

end

