#include <SymmetricClientAuthenticator.h>
#include <Crypto.h>
#include <ChaCha.h>

/**
 * @file ChaChaAuthenticator.cpp
 * @author Bijan Safai
 * @brief Implementation of SymmetricClientAuthenticator using the ChaCha cryptosystem
 * @version 0.1
 * @date 2021-11-08
 * 
 * @copyright Copyright (c) 2021
 * 
 */
using namespace ClientAuth;

class ChaChaClientAuthenticator : SymmetricClientAuthenticator
{

    private:
        ChaCha *_chacha;

        void SetState(uint8_t *nonce, int nonceSize)
        {
            _chacha->clear();
            _chacha->setKey(_keyGetter->GetKey(), _keyGetter->GetKeySize());
            _chacha->setIV(nonce, nonceSize);
        }
    public:

        ChaChaClientAuthenticator(KeyGetter *keyGetter) : SymmetricClientAuthenticator(keyGetter)
        {
            _chacha = new ChaCha();
        }

        ~ChaChaClientAuthenticator()
        {
            // clear just to ensure key is wiped from mem
            _chacha->clear();
            delete _chacha;
        }

        void RespondToChallenge(uint8_t *nonce, int nonceSize, uint8_t *message, int messageSize, uint8_t *cipherBuffer)
        {
            // critical to reset the state of the cipher and inject new nonce
            SetState(nonce, nonceSize);

            // encrypt into buffer
            _chacha->encrypt(cipherBuffer, message, messageSize);

            // clear again to ensure no sensitive info is sitting clear in mem
            _chacha->clear();
        }
};
