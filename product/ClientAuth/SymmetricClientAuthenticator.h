#include <KeyGetter.h> 
/**
 * @file SymmetricClientAuthenticator.h
 * @author Bijan Safai
 * @brief Defines interface for generic client auth agnostic to tranmission medium or crypto algothrim
 * @version 0.1
 * @date 2021-11-08
 * 
 * @copyright Copyright (c) 2021
 * 
 */
namespace ClientAuth
{
    class SymmetricClientAuthenticator
    {
        public:
            SymmetricClientAuthenticator(KeyGetter *keyGetter)
            {
                _keyGetter = keyGetter;
            }

            ~SymmetricClientAuthenticator()
            {
                delete _keyGetter;
            }

            virtual void RespondToChallenge(uint8_t *nonce, int nonceSize, uint8_t *message, int messageSize, uint8_t *cipherBuffer) = 0;
        
        protected:
            KeyGetter *_keyGetter;
    };
}