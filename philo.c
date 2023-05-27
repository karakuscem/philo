#include "philo.h"

// Create a struct for store necessary data.
// Take arguments and place them in struct. (Init function)
// Create a routine function
// Create a print function
// Create a start simulation function
// Create a free simulation function

int main(int argc, char **argv)
{
    t_data *simulation;

    if (argc < 5 || argc > 6)
        return (1);
    simulation = malloc(sizeof(t_data));
    if (!simulation)
        return (1);
    if (init_simulation(simulation, argc, argv))
        return (1);
    if (start_simulation(simulation))
        return (1);
    free_simulation(simulation);
    return (0);
}
