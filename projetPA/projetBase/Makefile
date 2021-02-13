all: projet                                                                  
                                                                                
projet: fonction.o projet.o                                                       
	gcc -o $@ $^                                                            
                                                                                
fonction.o: fonction.c projet.h                                                     
	gcc -c $<                                                               
                                                                                
projet.o: projet.c projet.h                                   
	gcc -c $<                                                               
                                                                                
clean:                                                                          
	rm -f *.o projet       
