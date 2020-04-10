n = 3; %размерность
R=[1 2 3]; 
A=sprandsym(10, 1, R); %задание матрицы по заданным собственным числам
A1 = zeros(10, 10);
arr = A+A1; %поскольку матрица разреженна€, делаем из нее обычную, добавл€€ нулевую
cond = norm(arr, 1)*norm(arr^(-1), 1)
%determinant = det(arr)
%b = rand(n,1);
f = fopen('C:\Users\Olexey\Desktop\числаки\Ћабка4\matrix\matrix\matrix1.txt', 'w');
fprintf(f, "%i \r\n", n);
fprintf(f, "%.6f ", arr);
fprintf(f, '\r\n');
fprintf(f, '%.6f \r\n', cond);
%fprintf(f, '%.20f \r\n', determinant);
fclose(f);
%f = fopen('C:\Users\Olexey\Desktop\числаки\Ћабка3\матрицы\матрицы\vecto7.txt', 'w');
%fprintf(f, "%.6f \r\n", b);
%fclose(f);