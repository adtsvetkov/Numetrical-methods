%�������� ������ ������������� �������
n = 10;
D = eye(n); 
E = eye(n);
D(n, n) = 2; %������ ������������
W = rand(n, 1); %����������� ������ W
nr = norm(W, 2);
H = E-2*W*W'*(nr^2);
A = H*D*H'
cond = norm(A, 1)*norm(A^(-1))
determinant = det(A)
f = fopen('C:\Users\Olexey\Desktop\�������\�����3\�������\�������\matrix3.txt', 'w');
fprintf(f, '%i \r\n', n);
fprintf(f, '%.6f ', A);
%fprintf(f, '\r\n');
%fprintf(f, '%.6f \r\n', cond);
fclose(f);