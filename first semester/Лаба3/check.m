function ch = check(string1, string2)
f = fopen(string1, 'r');
n = fscanf(f, "%i", [1 1]);
fclose(f);
f = fopen(string2, 'r');
b = fscanf(f, "%lf", [n 1])
bnew = fscanf(f, "%lf", [n 1])
n = norm(bnew, 2);
fclose(f);
end