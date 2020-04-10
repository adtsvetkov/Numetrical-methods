function ed = edit(string1, string2)
f=fopen(string1,'r');
n = fscanf(f, '%i', [1 1]);
A = fscanf(f, '%lf', [n n])
fclose(f);
f = fopen(string2, 'r');
b = fscanf(f, '%lf', [n 1]);
fclose(f);
At = A';
Anew = A*At;
bnew = A*b
norm(bnew, 1)
eig(Anew)
cond1 = norm(Anew, 1)*norm(Anew^(-1));
determinant1 = det(Anew);
f=fopen(string1,'a');
fprintf(f, '\r\n');
fprintf(f, '%.6f ', Anew);
fprintf(f, '\r\n');
fprintf(f, '%.6f \r\n', cond1);
fprintf(f, '%.6f', determinant1);
fclose(f);
f=fopen(string2, 'a');
fprintf(f, '%.6f\r\n', bnew);
fclose(f);
end