function []=testRng(seed, iters)

m = 2^31;
a = 2^16+3;
b = 7;

myrng = @(x) mod(a*x + b, m);

n = 500;
A = zeros(n,n);
x0 = seed;

for k = 1:iters

  x1 = myrng(x0);
  x2 = myrng(x1);
  
  x = ceil((x0/m)*n);
  y = ceil((x1/m)*n);
  c = ceil((x2/m)*4);
  x0 = x2;
  A(x,y) = c;
endfor

imagesc(A); colorbar; colormap(copper);
  
endfunction