file = fopen("grid_4.txt", 'rt');
[M, N] = fscanf(file, '%f %f', [2 inf]);
fclose(f);
X = M(1:2:N);
Y = M(2:2:N);
% x1 = 0:0.0001:2*pi;
% y1 = 2*cos(x);
% %plot (x1, y1, "r*");
% hold on
% Y-y1
% plot (x, Y-y1, "k-");