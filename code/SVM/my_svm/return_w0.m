function [w0] = return_w0(alpha, K, Y)

    w0 = 0;
    
    N = size(K, 1);
    
    for i = 1:N
        x = sum(alpha .* Y .* K(:, i));        
        w0 = w0 + ( Y(i) -  x );
    end
    
    w0 = w0/N;

end