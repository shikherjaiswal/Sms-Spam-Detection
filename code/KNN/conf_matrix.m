function [ conf ] = conf_matrix( Y, pred_Y )

[m,~] = size(Y);
conf = zeros(2,2);
for i=1:m
    conf(Y(i)+1, pred_Y(i)+1) = conf(Y(i)+1, pred_Y(i)+1) + 1;
end

end

