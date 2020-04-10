f = fopen("file3.txt", "r");
eps = fscanf(f, "%lf", [13 1])
ob = fscanf(f, "%i", [13 1])
%krya = fscanf(f, "%i", [10 1]);
%ob/2
figure
%loglog (eps, krya, 'k');
loglog (eps, ob, 'r');
hold on
grid on
title("Объем вычислений от заданной точности");
xlabel("Заданная точность eps");
ylabel("Объем вычислений");