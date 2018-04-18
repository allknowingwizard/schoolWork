function money=gamblersRuin(money,initBet,maxIters)  
  
   % 
   %
   % 
   winProb=0.49; % 
   moneyHistory=zeros(maxIters,1); 
   moneyHistory(1) = money; 
   bet = initBet; 
   for k=2:maxIters 
      r = rand(); 
      if r < winProb 
        money = money+bet; 
        bet = initBet; 
      else 
        money = money-bet; 
        bet = min(2*bet,money);
        if money <=0 
          break;
        end
      end
      moneyHistory(k) = money;    
   end
   plot(moneyHistory(1:k));
   
  
  
  
  
  
  
end