% 2-nd function

A = -2.0;
B = 2.0;

step = 0.001;

X_f = A:step:B;
Y_f = f2(X_f);

figure;
subplot(2,2,1);
title('n = 5');
PrintFun('grid_1.txt', X_f, Y_f);
subplot(2,2,2);
title('n = 10');
PrintFun('grid_2.txt', X_f, Y_f);
subplot(2,2,3);
title('n = 25');
PrintFun('grid_3.txt', X_f, Y_f);
subplot(2,2,4);
title('n = 50');
PrintFun('grid_4.txt', X_f, Y_f);
