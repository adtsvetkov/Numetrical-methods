function sol = solve(string1, string2)
f=fopen(string1,'r');
n = fscanf(f, '%i', [1 1])
A = fscanf(f, '%lf', [n n])
cond = norm(A, 1)*norm(A^(-1))
determinant = det(A)
fclose(f);
f = fopen(string1, 'a');
fprintf(f, '\r\n');
fprintf(f, '%.6f \r\n', cond);
fprintf(f, '%.6f', determinant);
fclose(f);
b = randn(n, 1);
f = fopen(string2, 'w');
fprintf(f, '%.6f\r\n', b);
fclose(f);
end