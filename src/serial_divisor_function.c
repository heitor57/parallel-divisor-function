#include <stdbool.h>
#include <stdlib.h>

bool *serial_divisor_function_sieve_of_eratosthenes(int limit) {
    bool *prime = malloc((limit + 1) * sizeof(bool));
    memset(prime, true, (limit + 1) * sizeof(bool));

    for (int i = 2; i * i <= limit; i++) {
        if (prime[i] == true) {
            for (int j = i * i; j <= limit; j += i) prime[j] = false;
        }
    }
    return prime;
}

int serial_divisor_function_df(int number, int *primes, int num_primes) {
    int prime, count, num_divisors = 1;
    for (int i = 0; i <= num_primes; i++) {
        prime = primes[i];
        count = 0;
        if (number % prime == 0) {
            while (number % prime == 0) {
                number = number / prime;
                count++;
            }
            num_divisors = num_divisors * (count + 1);
        }
    }
    return num_divisors;
}