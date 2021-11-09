#include <string.h>

namespace ClientAuth
{
    /**
     * @brief Abstract class defines a key aquisition interface. 
     * 
     */
    class KeyGetter
    {
        public:
            virtual uint8_t* GetKey() = 0;
            virtual int GetKeySize();
    };

    /**
     * @brief Most basic possible implementation of key aquasition. The key is held in mememory in cleartext. Prob should'nt be used in production.
     * 
     */
    class InMemoryKeyGetter : KeyGetter
    {
        private:
            uint8_t *_keyBuffer;
            int _keySize;

        public:
            InMemoryKeyGetter(uint8_t *keyBuffer, int keySize)
            {
                _keyBuffer = keyBuffer;
                _keySize = keySize;
            }

            ~InMemoryKeyGetter()
            {
                //write over key in memory so it cant be extracted
                memset(_keyBuffer, 0xBA, sizeof(_keyBuffer));
                delete _keyBuffer;
                _keySize = 0;
            }

            uint8_t* GetKey() { return _keyBuffer; }
            int GetKeySize() { return _keySize; }
    };
}