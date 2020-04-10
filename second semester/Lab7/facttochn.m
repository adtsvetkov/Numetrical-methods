function facttochn(string1, string2)
f = fopen(string2, "r");
eps = fscanf(f, "%lf", [10 1])
fact = fscanf(f, "%lf", [10 1])
figure
loglog (eps, fact);
hold on
grid on
title(string1);
xlabel("eps");
ylabel("Фактическая точность");
fclose(f);
end