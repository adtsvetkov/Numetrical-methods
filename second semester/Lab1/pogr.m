function p = pogr(string, string1)
f = fopen(string, 'r');
%Y = fscanf(f, '%lf', [200 1])
%x = fscanf(f, '%i', [200 1])
Y = fscanf(f, '%lf', [20 1]);
x = fscanf(f, '%lf', [20 1]);
figure
grid on
for n=1:19
    semilogy([x(n, 1), x(n+1, 1)],[Y(n, 1), Y(n+1, 1)]);
    hold on
end
title(string1)