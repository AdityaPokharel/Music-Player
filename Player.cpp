//
// Created by Aditya Pokharel on 7/18/17.
//
#include <iostream>
#include <string>
#include <SDL2/SDL.h>

struct Audio{
    Uint32 length;
    Uint8* position;
    
};

void play(void* data, Uint8* stream, int audio_length){
    Audio* audio = (Audio*) data;

    if(audio->length == 0){
        return;
    }

    Uint32 length = (Uint32) audio_length;
    length = length > audio->length? audio->length : length;

    SDL_memcpy(stream, audio->position, length);

    audio->position += length;
    audio->length -= length;
}

int main(int argc, char** argv){

    if(argc != 2){
        std::cerr << "Usage: ./Play /path/to/file" << std::endl;
        return -1;
    }

    SDL_Init(SDL_INIT_AUDIO);


    //Information about the audio file. //
    Uint8* start;                       //array of file info (eg. how loud the wave is, etc)
    Uint32 length;                      //
    SDL_AudioSpec spec;                 //specifications of the output device
    char* audio_file = argv[1];         //
    std::string filename = audio_file;  //


    //Checks whether file is a .wav file.
    std::string file_extension = filename.substr(filename.find_last_of(".") + 1);
    if(!(file_extension == "wav" || file_extension == "WAV")){
        std::cerr << "Error, program only works with .wav files." << std::endl;
        return 1;
    }

    if(SDL_LoadWAV(audio_file, &spec, &start, &length) == NULL){
        std::cerr << "Error, cannot load WAV file" << std::endl;
        return 1;
    }

    Audio audio;
    audio.position = start;
    audio.length = length;
    spec.callback = play; //func pointer
    spec.userdata = &audio;

    //Audio device object.
    SDL_AudioDeviceID device = SDL_OpenAudioDevice(NULL, 0, &spec, NULL, SDL_AUDIO_ALLOW_ANY_CHANGE);
    if(device == 0){
        std::cerr << "Error, cannot find device." << std::endl;
        return 2;
    }

    //Plays the audio file.
    SDL_PauseAudioDevice(device, 0);
    while(audio.length > 0){
        SDL_Delay(100);
    }

    SDL_CloseAudioDevice(device);
    SDL_FreeWAV(start);
    SDL_Quit();
    return 0;

}
