function [root,fRoot,k]=stammeraHybrid(f,a,b,xTol)
 % I will some of the prelim work started...   
 fa=f(a);
 fb=f(b); 
 if fa*fb> 0
    fprintf('\nWarning: [a,b] Not a valid bracketing interval\n');
    fprintf('  Returning Null Solution\n');
    root=[]; 
    fRoot=[];
    return;
 elseif fa==0
    fprintf('Lucky Guess\n');
    root=a; fRoot=fa; 
    return;
 elseif fb==0
    fprintf('Lucky Guess\n');
    root=b; fRoot=fb; 
 end  
 maxIters= ceil(log(abs(b-a)/xTol)/log(2));
 k=maxIters;
 % START DOING STUFF HERE! 
 x0=a;
 x1=b;
 f0=fa;
 f1=fb;
 doSecant=1;
 lastStep = doSecant;
 fence = 1e-4;
 
 for i = 1:maxIters
     
    printf("Iter %d:\n", i);
    %secant loop
    if doSecant == 1
      
      
      
      
      
      
      #{
      printf("Secant!\n");
      x2=(x0*f1 - x1*f0)/((f1-f0)+1e-99);
      f2=f(x2);
      if (x2>b) || (x2<a) || (f1==f2)
        doSecant=-1;
      else
        if(f(x1)==0)
          root=x1*1.0;
          fRoot=f(x1*1.0);
          k=i;
          return;
        end
        x0=x1;
        f1=f0;
        x1=x2;
        f2=x2;
        lastStep = 1;
      end
      #}
    end
    
    
    %bisection loop
    if doSecant < 1
      
          m = 0.5*(a+b);
        Fm = F(m);
        %if strcmp(printResults,'true');
            fprintf('Iter %d\n',k);
            fprintf('   a=%20.16f     b=%20.16f     m=%20.16f\n',a,b,m);
            fprintf('F(a)= %5.3e           F(b)= %5.3e            F(m)= %5.3e \n',Fa,Fb,Fm);
            fprintf('-----------------------------------------------------------------------\n');
            pause;
        %end
        if Fa*Fm > 0  % set a=m, keep b as is 
            a=m;
            Fa=Fm;
        elseif Fb*Fm > 0 % set b=m, keep a as is 
            b=m;
            Fb=Fm;
        elseif Fm==0
            break;  % landed on the root 
        end
      
      
      #{
        printf("Bisecting!\n");
        m=0.5*(a+b);
        fm=f(m);
        if(fa*fm > 0)
          a=m;
          fa=fm;
        endif
        if(fb*fm > 0)
          b=m; 
          fb=fm;
        endif
        if(fm==0)
          root=m;
          fRoot=fm;
          k=i;
          return;
        endif
        doSecant = doSecant + 1;
        if(doSecant==1)
          x0=a;
          x1=b;
          f0=fa;
          f1=fb;
        endif
        #}
    end
    
    #{
    if(lastStep != 1)
      if(abs(b-a) < fence || f(0.5*(a+b)) == 0)
          root=0.5*(a+b);
          fRoot=f(root);
          k=i;
          return;
      endif
    elseif (abs(b-a) < fence)
      if ((abs(x1-x0)/abs(x0)) < fence)
        root=x1;
        fRoot=f(root);
        k=i;
        return;
      endif
    end 
    #}
    
    
    printf("  Best Guess Secant: %f, F(r): %d\n", x1*1.0, f(x1));
    printf("  Best Guess Bisect: %d, F(r): %d\n", (0.5*(a+b)), f(0.5*(a+b)));
    lastStep = 0;
 endfor


  root=NaN; % This is wrong
  fRoot=NaN; % This is wrong
  k=inf;

endfunction