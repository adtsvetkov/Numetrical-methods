function dr = draw(string1, string2)
f = fopen(string1, 'r');
uzel = fscanf(f, '%lf', [11 1]);
x = fscanf(f, '%lf', [1001 1]);
Y = fscanf(f, '%lf', [1001 1]);
pogr = fscanf(f, '%lf', [1 1]);
figure
x1 = 0:0.0001:2*pi;
y1 = 2*cos(x);
%plot (x1, y1, "r*");
hold on
Y-y1
plot (x, Y-y1, "k-");
pogr
end