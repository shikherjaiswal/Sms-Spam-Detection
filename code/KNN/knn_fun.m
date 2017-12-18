function [predicted_test_Y] = knn_fun(train_X, train_Y, test_X, k)

[m_train, n_train] = size(train_X);
[m_test, n_test] = size(test_X);

% make label matrix
no_classes = 2;
train_Y_matrix = zeros(m_train,no_classes);
for i=1:m_train
    train_Y_matrix(i,train_Y(i)+1) = 1;
end

train_Y_matrix;
% code for knn
predicted_test_Y = zeros(m_test,1);

for i=1:m_test
 
    diff = train_X(:,1:n_train) - repmat(test_X(i,:),[m_train 1]);
    euc_dist = sum(diff.^2,2);
    
    [~, indices] = sort(euc_dist);
    y_matrix = zeros(1, no_classes);
    for j=1:k
     y_matrix = y_matrix + train_Y_matrix(indices(j),:);
    end
    
    max_indices = find(y_matrix == max(y_matrix));
    predicted_test_Y(i) = max_indices(1)-1;
    
end