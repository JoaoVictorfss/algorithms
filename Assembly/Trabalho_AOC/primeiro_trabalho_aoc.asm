###############################################################   
#       
#@author João Victor Fernandes de Souza Silva
#@data   23/09/2020
#@dsc    Primeiro trabalho de AOC, programa que lê um arquivo,
#        transforma os dados em inteiros e os ordenam, através 
#        do algoritmo quicksort.
#
###############################################################          

.data
         arr:     .space 40000        #10000 inteiros vezes 4, quantidade de dados do arquiv
         aux:     .space 5
         buffer:  .space 60000        #60 kilobytes, tamanho estimado do arquivo
         file:    .asciiz "numeros.csv"
	 str1:    .asciiz "\n"
.text
###############################################################          
 	 #abre o arquivo para leitura
 	 li       $v0, 13       
 	 la       $a0, file     
 	 li       $a1, 0        
 	 li       $a2, 0        
 	 syscall                
  	 move     $s0, $v0      

 	 #lê do arquivo aberto
	 li       $v0, 14       
	 move     $a0, $s0      
	 la       $a1, buffer   
 	 li       $a2, 60000        
	 syscall   

         #fecha o arquivo
	 li       $v0, 16       
	 move     $a0, $s0     
	 syscall                      
###############################################################          
         jal      atoi
         add      $s0, $zero, $v0    # size 
	 addi     $a0, $s0, -1       # high
	 add      $a1, $zero, $zero  # low
	
	 jal      sort 
	
	 jal      print
	
	 li	  $v0, 10
	 syscall
###############################################################          
#function atoi     
atoi:    
	 sw	  $ra,  0($sp)
	 sw	  $s0, -4($sp)
	 sw       $s1, -8($sp)
	 sw	  $s2, -12($sp)
	 sw	  $s3, -16($sp)
	 sw	  $s4, -20($sp)
	 addi	  $sp, $sp, -24  
		    
         la       $t9, arr
	 add      $t8, $zero, $zero  #tamanho do array de numeros               
	 la       $s0, buffer     
         addi     $s1, $zero, 44     # vírgula em decimal  
         addi     $s2, $zero, 32     # espaço em decimal
         la       $s3, aux
         addi     $t1, $zero, 0      #cont j = 0
                 
WHILE:	 lb       $s4, 0($s0)
         beq      $s4, $zero,CONV 
         beq      $s4, $s1, CONV
         beq      $s4, $s2, SAI      
 
         sb       $s4, 0($s3)          	 

	 addi     $t1, $t1, 1
         addi     $s3, $s3, 1         
SAI:	 beq      $s4, $zero, RET_ATOI
         addi     $s0, $s0, 1
         j        WHILE 


###############################################################          
CONV:	       
         addi     $s3, $s3, -1
         addi     $t1, $t1, -1
         addi     $t2, $zero, -1
         
         addi     $t3, $zero, 1      #casa decimal atual
         add      $t4, $zero, $zero  #número auxiliar
         
         #para cada caractere       
WHILE2:	 lb       $t0, 0($s3)
         beq      $t1, $t2, SAI2 
         ################################
         #Transforma os caracteres em inteiro  
         add      $t5, $zero, $zero  #valor inteiro correspondente ao '0' na tabela ASCII
         addi     $t6, $zero, 48     #'0' 
WHILE3:  beq      $t0, $t6, PROX
         addi     $t6, $t6, 1        #prox char da tabela ACII
         addi     $t5, $t5, 1        #inteiro associado a $t6
         j        WHILE3         	 
PROX:    
	 ################################
         #Multiplica cada valor inteiro por sua casa decimal. O número auxiliar
         #vai receber a soma de cada multiplicação e no fim salva no array o valor inteiro total
	 mul      $t5, $t3, $t5 
         add      $t4, $t4, $t5

	 addi     $s3, $s3, -1
	 addi     $t1, $t1, -1
	 addi     $t5, $zero, 10
	 mul      $t3, $t3, $t5      #próxima casa decimal
	 j        WHILE2        
     	 ################################
     	 #escreve no array de números o resultado e incrementa a qtd de elementos
SAI2:    
         sw       $t4, 0($t9)        #*arr = numero
         addi     $t9, $t9, 4        #&arr ++ 
         addi     $t8, $t8, 1        #tamaho do array ++
	 		
         la       $s3, aux
         add      $t1, $zero, $zero
         j        SAI
         ################################ 
RET_ATOI: 
         lw	  $s4, 4($sp)
         lw	  $s3, 8($sp)
	 lw	  $s2, 12($sp)
	 lw	  $s1, 16($sp)
	 lw	  $s0, 20($sp)
	 lw	  $ra, 24($sp)
	 addi	  $sp, $sp, 24 
	 add      $v0, $zero, $t8    #retorna o tamanho do array de números 
	 jr       $ra
###############################################################          
#function sort( arr, low, high)
sort: 
        sw    	  $ra, 0($sp)
        sw        $a0, -4($sp)
        sw        $a1, -8($sp)  
        addi      $sp,$sp, -12   
        
        #if (high/ao > low/a1) return => outra chamada
        beq       $a1, $a0, RETURN   
        slt       $t0, $a0, $a1    
        beq       $t0, $zero, CALL   #a0 > a1, call
        
        #else 
RETURN:   
        addi      $sp,$sp, 12        #volta 12 endereços na pilha  
        jr        $ra  
                       
CALL:   
        jal       part      
        addi      $a0, $v0, -1       #high = j - 1
        jal       sort     
        
        lw        $a1, 4($sp)   
        lw        $a0, 8($sp) 
        lw        $ra, 12($sp)            
        addi      $a1, $v0, 1        #low = j + 1    
        jal       sort 
        
        #Ponto de retorno     
        lw        $a1, 4($sp)   
        lw        $a0, 8($sp)           
        lw        $ra, 12($sp)   
        addi      $sp,$sp, 12  
        jr        $ra
###############################################################          
#function partition(int *arr, int low, int high)  
part:
        sw        $ra, 0($sp)
        sw        $a0, -4($sp)       
        sw        $a1, -8($sp)       
        sw        $s1, -12($sp)
        sw        $s2, -16($sp)
        addi	  $sp, $sp, -20
	
        #pivot = arr[high]
        la        $s1, arr
        addi      $t0, $zero, 4
        mul       $t0, $a0, $t0 
        add       $s1, $s1, $t0
     	lw        $t0, 0($s1)        #pivot
     	     
     	addi      $t1, $a1, -1       #i = (low - 1);

        #for (j = low; j <= high - 1; j++)
        add       $t2, $zero, $a1    #j = low
        addi      $t3, $a0, -1       #cmp = high - 1
        
        #para array na posição j
        la        $s1, arr        
        addi      $t5, $zero, 4
        mul       $t5, $t2, $t5    
        add       $s1, $s1, $t5      #endereço de arr[j] 
         
FOR:    
        #se j <= high - 1
        beq       $t2, $t3, CONTINUE
        slt       $t4, $t2, $t3
        bne       $t4, $zero, CONTINUE
        
        #se j > high - 1
        j         P_RETURN           #sai do for
                     
CONTINUE:
        #if (arr[j] < pivot)
     	lw        $t5, 0($s1)        #arr[j]	
        slt       $t4, $t5, $t0
        bne       $t4, $zero, SWAPP	
        j         BREAK
      
SWAPP: 
        addi      $t1, $t1, 1        #i++    

        la        $s2, arr           
        addi      $t6, $zero, 4
        mul       $t6, $t1, $t6
        add       $s2, $s2, $t6
        
     	lw        $t6, 0($s2)        #arr[i]
    	  	
     	sw        $t5, 0($s2)        #arr[i] = arr[j]
        sw        $t6, 0($s1)        #arr[j] = arr[i]
     	   
BREAK: 
        addi      $t2, $t2, 1        #j++
        addi      $s1, $s1, 4        #proximo elemento
        j         FOR
           
    
P_RETURN: 
     	addi      $v0, $t1, 1 #retorna j = i + 1 
     	#swap(&arr[i + 1], &arr[high]);	
        la        $s1, arr           
        addi      $t6, $zero, 4
        mul       $t6, $v0, $t6
        add       $s1, $s1, $t6
     	lw        $t6, 0($s1)        #arr[i + 1]
     	
     	#arr[high]
        la        $s2, arr
        addi      $t5, $zero, 4
        mul       $t5, $a0, $t5
        add       $s2, $s2, $t5
     	lw        $t5, 0($s2)        #arr[high]
     	
     	sw        $t5, 0($s1)
     	sw        $t6, 0($s2)
     	
     	#recupera o estado original dos registradores
        lw        $s2, 4($sp)
        lw        $s1, 8($sp)
     	lw        $a1, 12($sp)
     	lw        $a0, 16($sp)
     	lw        $ra  20($sp)
     	addi	  $sp, $sp, 20
     	
     	jr        $ra
###############################################################          
#function print
print:	
	#mostra array
	sw    	  $ra, 0($sp)
        sw        $a0, -4($sp)
        sw        $s1, -8($sp)  
        addi      $sp,$sp, -12  
        
	la        $s1, arr
        add       $t0, $zero, $zero   #i=0       	
FOR0:   beq       $t0, $s0, EXIT
        lw        $t1, 0($s1)
        
        addi 	  $v0, $zero, 1
        add  	  $a0, $zero, $t1
        syscall
        
        addi	  $v0, $zero, 4 
        la	  $a0, str1
        syscall
        
        addi      $t0, $t0, 1        #i ++  
        addi      $s1, $s1, 4 
        j         FOR0
	
EXIT:   
        lw        $s1, 4($sp)   
        lw        $a0, 8($sp)           
        lw        $ra, 12($sp)   
        addi      $sp,$sp, 12 
         
        jr        $ra
###############################################################          





