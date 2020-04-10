f = fopen("file5.txt", "r");
eps = fscanf(f, "%lf", [10 1])
fact = fscanf(f, "%lf", [10 1])
x = 0.0000000001:0.0000001:0.1;
y = x;
figure
loglog (eps, fact);
hold on
grid on
loglog(x, y);
title("Фактическая точность от заданной");
xlabel("eps");
ylabel("Фактическая точность");
fclose(f);