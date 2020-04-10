%рандомим плохо обусловленную матрицу Гильберта
n=3;
for i = 1:1:n
    for j = 1:1:n
        C(i, j) = 1/(i+j-1);
    end
end
cond1 = norm(C, 1)*norm(C^(-1))
determinant = det(C)
b1 = randn(n, 1);
f = fopen('C:\Users\Deadpool\Desktop\числаки\Лабка2\Работа с матрицами\Работа с матрицами\matrix2.txt', 'w');
fprintf(f, '%i \r\n', n);
fprintf(f, '%.6f ', C);
fprintf(f, '\r\n');
fprintf(f, '%.6f \r\n', cond1);
fclose(f);
f = fopen('C:\Users\Deadpool\Desktop\числаки\Лабка2\Работа с матрицами\Работа с матрицами\vector2.txt', 'w');
fprintf(f, '%.6f\r\n', b1);
fclose(f);