function PrintFun( str, X_f, Y_f )
    file = fopen(str, 'rt');
    [M, N] = fscanf(file, '%f %f', [2 inf]);
    X = M(1:2:N);
    Y = M(2:2:N);
    grid on;
    hold on;
        plot(X_f, Y_f);
        plot(X, Y);
    fclose(file);
end

