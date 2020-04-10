function tochnshag(string1, string2)
f = fopen(string2, "r");
shag = fscanf(f, "%i", [20 1])
fact = fscanf(f, "%lf", [20 1])
figure
semilogy (shag, fact);
hold on
grid on
title(string1);
xlabel("Шаг");
ylabel("Фактическая точность");
fclose(f);
end