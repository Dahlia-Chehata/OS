#include <pthread.h>

struct station {
    //mutex
	pthread_mutex_t mutex;
	//conditional variables
	pthread_cond_t trainFull_cond ,noAvailableSeat_cond,trainArrivalSignal_cond;
	//onTrain_passengers: are already in train
	//waiting_passengers: are unboaeded yet
	//seats_available: are the empty seats yet
	int onTrain_passengers,waiting_passengers,seats_available;
};

void station_init(struct station *station);

void station_load_train(struct station *station, int count);

void station_wait_for_train(struct station *station);

void station_on_board(struct station *station);
