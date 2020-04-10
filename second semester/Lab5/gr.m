f = fopen("file5.txt", "r");
x1 = fscanf(f, "%lf", [16 1])
y = fscanf(f, "%lf", [16 1])
x=0:0.01:1.5
f = sin(x)+cos(x);
figure
plot (x1, y);
hold on
grid on
plot(x, f);
title("График точного решения и посчитанного по правилу Эйлера-Коши");
xlabel("x");
ylabel("y");
%legend('S_h', 'S_2_h', 'Правило Рунге');
fclose(f);