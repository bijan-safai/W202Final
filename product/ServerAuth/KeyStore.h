#include <string.h>

namespace ServerAuth
{
    /**
     * @brief Class abstracts retriving a key from a keystore by some id. 
     * 
     */
    class KeyStore 
    {
        public:
        /**
         * @brief Retrives a key from some store
         * 
         * @param keyId Identifier of key
         * @param keyBuffer Output buffer to write key to
         * @return If the key was found
         */
        virtual bool GetKey(int keyId, uint8_t *keyBuffer) = 0
    };

    // Super simple key store for testing only. Will always return the same key.
    class TestKeyStore : KeyStore 
    {
        private:
        uint8_t *_keyBuffer;

        public:
        TestKeyStore(uint8_t *keyBuffer)
        {
            _keyBuffer = keyBuffer;
        }

        ~TestKeyStore()
        {
            //write over key in memory so it cant be extracted
            memset(_keyBuffer, 0xBA, sizeof(_keyBuffer));
            delete _keyBuffer;
        }

        void GetKey(int keyId, uint8_t *keyBuffer)
        {
            std::memcpy(keyBuffer, _keyBuffer sizeof(keyBuffer));
            return true;
        }
    };
}
