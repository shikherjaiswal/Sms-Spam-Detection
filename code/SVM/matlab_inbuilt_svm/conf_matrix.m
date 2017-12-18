function [ acc, conf ] = conf_matrix( Y, pred_Y )

Y(Y==-1) = 0;
pred_Y(pred_Y==-1) = 0;
[m,~] = size(Y);
conf = zeros(2,2);
for i=1:m
    conf(Y(i)+1, pred_Y(i)+1) = conf(Y(i)+1, pred_Y(i)+1) + 1;
end

acc = sum(conf(1,1) + conf(2,2)) / sum(conf(1,1) + conf(1,2) + conf(2,1) + conf(2,2));
end

