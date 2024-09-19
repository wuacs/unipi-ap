My solution of the projects listed in [this pdf file](/untypedlambda/1/lambda.pdf)

1. Project 1:
    1. *greater than* is easily derivable from the *greater than or equal* function showed in page 7. 

        In particular a natural N is strictly greater than a natural M iff N - 1 is greater than or equal than M.

        $G' \equiv (\lambda xy. Z((Px)Py))$

    2. *less than* is then easily derivable from *greater than*:

        $L' \equiv (\lambda xy. G'yx)$

2. Project 2:
    1. We can encode any positive integer of absolute value x as $\lambda z. zx0$ and consequently we can encode the negative 
        x with $\lambda z.z0x$.

        Thus, zero is encoded as the pair $\lambda z.z00$.

3. Project 3:
    1. *addition* requires 3 subfunctions: 
        1. if the two integers are both negative or both positive we can simply add the corresponding parts.
            this can be encoded as $h_1 \equiv \lambda kxy. ((\lambda t. (\lambda z. z(k(t0)(0t))))((kx)S(ky)))$.
        2. If the integers do not share the same sign we need to first determine which integer is greater, in absolute value, say z and then create an
        integer with sign as z and the value as z - (the other integer's value).
            this can be encoded as $h_2 \equiv \lambda xy. (G x y (\lambda z. z0(yPx)) (\lambda z. z(xPy)0)) $
    
    Thus the sum of integers is: $$A'\equiv \lambda xy.Z(T x)\;(Z(T y) (h_1 F x y) (h_2 (F x) (T y)))\; (Z(T y) (h_2 (F y) (T x)) (h_1 T x y))$$

    2. *subtraction* can be viewed in terms of the addition by just swapping the position of the natural number in the second term.
    $$
        S' \equiv \lambda xy. Z (T y) (A' x (\lambda z. z(F y)0)) (A' x (\lambda z. z0(T y)))
    $$

4. Project 4: 
    Our division of positive integers will behave in the typical way when two integers are not divisible, i.e. if n % m != 0 then we will return k so that
    k * m + n % m = n.
    Of course we will use the fix-point combinator in our definition and we need a fix-point of the division i.e.:
    $$D \equiv \lambda f.\lambda n.\lambda d. Z(T (S' n d)) (Z (F (S' n d)) (1,0) (0,0)) (A' (1,0) (f (S' n d) d))$$
    thus our definition of division will just be 
    $$D' = \lambda ab.(Y D)a b$$
    where Y is the fix-point combinator.
    Thus 
    ```
    D = (Y D') 8 3 = D' (Y D') 8 3 = 1 + (Y D') 5 3  = 1 + D' (Y D') 5 3 = 1 + 1 + (Y D') 2 3 = 1 + 1 + D (Y D') 2 3 = 1 + 1 + 0 = 2
    ```

5. Project 5:
    We suppose the use of naturals
    A fix-point for factorial is:
    $$
    F' \equiv \lambda f.\lambda n. Z (P n) (1) (mul n (f (P n)))
    $$
    So factorial is $$F \equiv \lambda n. (Y F') n$$

6. Project 6:
    Any rational number can be obtained as the division of two integers. Thus we can re-use the definition of division and extend our definition of integer:
    
    The rational number p/q is encoded as $\lambda z.zpq$ where pq are themselves pairs.

    Note that our definition of integers is biijective, i.e. any pair represents a distinct and unique integer.

    Rationals instead are defined through the notion of division: thus p = (4,0) q = (2,0) create the same rational number as p = (8, 0) and q = (4, 0).

7. Project 7:
    First we define an helper function which taken an integer returns its natural number corresponding(i.e. its absolute value):

    $$
    L' \equiv \lambda x. Z (T x) (T x) (F x)
    $$

    Then we define another helper function which takes two numbers and returns True if they are of the same sign, false otherwise.
    $$
    E' \equiv \lambda xy. Z (T x) ((Z (T y)) T F) (Z (F y) T F)
    $$

    $$
    M' \equiv \lambda xy. E' x y ((L' x) (A' y) x) ((L' x) (A' (S' y (0,0))) x)
    $$

    We also extend the definition of division between integers, since we want to be able to divide with numbers with different sign.

    $$
    D' = \lambda ab. E' a b ((Y D') (\lambda z.z(L' a)0) (\lambda z.z(L' b)0)) (S' (0,0) ((Y D') (\lambda z.z(L' a)0) (\lambda z.z(L' b)0)))
    $$

    Addition between rationals:
    $$
    \lambda xy. (\lambda z. z(A' (D' (M' (F x) (F y)) (T x)) (D' (M' (F x) (F y)) (T y)))(M' (F x) (F y))) 
    $$

    Subtraction (lazy) between rationals:
    $$
    \lambda xy. (\lambda z. z(S' (D' (M' (F x) (F y)) (T x)) (D' (M' (F x) (F y)) (T y)))(M' (F x) (F y))) 
    $$

    Multiplication between rationals:
    $$
    M'' \equiv \lambda xy. (\lambda z. z(M' (T x) (T y))(M' (F x) (F y))) 
    $$

    Division between rationals:
    $$
    \lambda xy. (M'' x (\lambda z. z(F y)(T y)))
    $$

8. Project 8:
    1. A list of numbers, say naturals, say $a_1,a_2, a_3$ can be viewed as, $\lambda z.za_1(\lambda z'.z'a_2(\lambda z''.z''a_3 null))$
        
        Where null can be arbitrarly encoded.
        
        Thus we can access $a_3$ through the application of True 3 times, which can be done via the general function access n : $\lambda n. \lambda l. (n T) l$
9. Project 9:
    1. It is simply access 1 from previous point.

10. Project 10:
    Our fix point is:
    $$
    C' \equiv \lambda f.\lambda l. N (F l) 0 (S 1 (f (F l))) 
    $$
    
    where N is a function which tests if a function is the null function and returns true if that is the case or zero.

    thus length is:
    $$
    L' \equiv \lambda l. (Y C') l
    $$