clc
clear

%% read input and output
X = read_input('super_reduced_examples.txt');
Y = read_output('output.txt');
Y(Y == 0) = -1;

%% select features

% X = select_features(X);

%% add extra features
X = [X read_input('extra_examples.txt')];
X = X(1:1000,:);
Y = Y(1:1000,:);
[mx, nx] = size(X);

%% shuffle data
rng(1);
perm = randperm(mx);
X = X(perm,:);
Y = Y(perm,:);

%% separate training and test data
% frac = 0.7;
% test_X = X(ceil(frac*mx)+1:end,:);
% test_Y = X(ceil(frac*mx)+1:end,:);
% X = X(1:ceil(frac*mx),:);
% Y = Y(1:ceil(frac*mx),:);

%% k-fold cross validation
[mx, nx] = size(X);
k = 10;
s = mx / k;
error = zeros(k,1);

for i=1:k
    fprintf('running on fold %d',i);
    valid_ind = ceil((i-1)*s) + 1 : ceil(i*s);
    train_ind = 1:mx;
    train_ind(valid_ind) = [];
    valid_X = X(valid_ind,:);
    train_X = X(train_ind,:);
    
    valid_Y = Y(valid_ind,:);
    train_Y = Y(train_ind,:);
    
    train_mean = mean(train_X);
    train_var = var(train_X);
   
    train_X = standardize(train_X, train_mean, train_var);
    valid_X = standardize(valid_X, train_mean, train_var);
    
    predicted_valid_Y = run_svm(train_X, train_Y, valid_X);
    error(i) = classification_error(valid_Y, predicted_valid_Y);
    
end

%% average error of all folds
avg_error = sum(error) / k;
avg_accuracy = 100-avg_error;
fprintf('error in %d folds = %f\n',k,avg_accuracy);
