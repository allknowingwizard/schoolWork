function [s,maxDrift] = biasedWalk(x,y,alpha,maxSteps) 
   % input args:  
   %   x,y:  Initial Positions 
   %   alpha:   bias parameter;  
   %   maxSteps:  maximum number of steps before walker gives up 
   % Output args: 
   %    s:    Number of steps it took to get home  
   %           OR  s=-1  indiciates home   %    was never reached
   %    maxDrift:   Farthest distance from home walker ever gets to. 
   s=-1; % set to failure initially 
   maxDrift=abs(x)+abs(y); 
   
   for k=1:maxSteps 
     % do biased random walk on an open universe   
  
     
     
      % TO LIST 
      %    Find the "weights" for each move 
      %    Convert weights to probabilities.
      %    draw random number between 0 and 1.
      %    decide on which move to make and make the move!
   
     
     
     
     
     
     % check to see if home is reached
     distToHome = abs(x)+abs(y); 
     if distToHome ==0 
         s=k;
         return; 
     elseif distHome > maxDrift
         maxDrift=distHome; 
     end % end checking 
    
   end % end stepping loop 
   
   
    
end