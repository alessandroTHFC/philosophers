# philosophers
Introduction into Threading and Mutex

The project is run using make followed by ./philosophers (Number of philosophers) (Time to Die) (Time to Eat) (Time to Sleep) <(optional) Times to Eat>
E.g. ./philosophers 4 500 100 100 
The expected output of which would be an endless looping of the program as the arguments dont allow for the philosophers to die.
  
Key Steps to building out this project are
1. Creating the error checking functions as all arguments must be: Within range of integer, A valid number (no letters, random character or negative number), Arguments also no  more or less than 5 or 6
2. Parsing the arguments into struct to contain all neccessary values for the project (I have 2 structs, one to contain main data for whole program and an array of structs to represent each philosophers data).
3. Making functionality to represent the philosophers lifecycle, eating, sleeping thinking. Also the function that will monitor the threads status to see if they have died.
5. Creating threads.

Key Concepts 
Within this project you will need to understand:
All the various thread functions(pthread_create, pthread_join, pthread_detatch).
All the various mutex functions(pthread_mutex_init, pthread_mutex_lock, pthread_mutex_unlock, pthread_mutex_destroy).
  
Also
Bare in mind the threads need to be delayed upon entering the function included when creating its thread. Offset them! 
Timing is extremely crucial in this project to the almost anal degree. Slightest mistiming just ruins everything. 
I chose to create a secondary thread per philosopher thread to monitor each philosopher thread, i've seen others just have one function in the main process that monitors the various philo struct values.
Potential issue with this is that it would need to loop through each philo struct checking each value, if there are lots of philo's this could cause an issue because philo one could die, 
but the program is looking at philo 8 when 1 dies so for the sake of timing it could realise the philo is dead too late. Food for thought.
