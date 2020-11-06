/*
 * FreeRTOS V202007.00
 * Copyright (C) 2020 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://aws.amazon.com/freertos
 * http://www.FreeRTOS.org
 */

#ifndef AWS_CLIENT_CREDENTIAL_KEYS_H
#define AWS_CLIENT_CREDENTIAL_KEYS_H

/*
 * @brief PEM-encoded client certificate.
 *
 * @todo If you are running one of the FreeRTOS demo projects, set this
 * to the certificate that will be used for TLS client authentication.
 *
 * @note Must include the PEM header and footer:
 * "-----BEGIN CERTIFICATE-----\n"\
 * "...base64 data...\n"\
 * "-----END CERTIFICATE-----\n"
 */
#define keyCLIENT_CERTIFICATE_PEM "-----BEGIN CERTIFICATE-----\nMIIDWjCCAkKgAwIBAgIVAILNOOLfnzYB2r+8T0BYrXzvXggWMA0GCSqGSIb3DQEB\nCwUAME0xSzBJBgNVBAsMQkFtYXpvbiBXZWIgU2VydmljZXMgTz1BbWF6b24uY29t\nIEluYy4gTD1TZWF0dGxlIFNUPVdhc2hpbmd0b24gQz1VUzAeFw0yMDExMDYwMTU2\nMDZaFw00OTEyMzEyMzU5NTlaMB4xHDAaBgNVBAMME0FXUyBJb1QgQ2VydGlmaWNh\ndGUwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQChwUKH0NRv/h8jeij3\nElCCrOTs3IjICenXyYFSUbo/pJdEkBhRwQ6R7aJY3ZnbpGdQbhiP8VRxj/cbAoi3\ngGrtZbfaUmvFCGfN/u2Mim36IS3pnz6zo/bFk+4RTJSyhjlQu5Tjzezf5XMjv4O0\n2cS3R16I+/xD4H6BsaxPsj4/+6/R8OSgenojHM3MEF9w9Ir08vT6OoGzdkNmcdtC\nJ7BG4Erf1sDYA8UE4zMzwAqJ9fKBH6O8BkXepql7+lwUFY4r+1AbTYcKf3uO6mQR\nW78Y/KEhy/fvBg+RReBqqXWjTzPITDKnSnBrLUrV7+Q5XMTj8gQ1G7xUFGKp4/t/\nxQBNAgMBAAGjYDBeMB8GA1UdIwQYMBaAFBDJmzmF58ZYSlrzUxg5hBhE27JSMB0G\nA1UdDgQWBBTCMFtCABs0hYYDpes0bQdqjgbREDAMBgNVHRMBAf8EAjAAMA4GA1Ud\nDwEB/wQEAwIHgDANBgkqhkiG9w0BAQsFAAOCAQEAJUMnDkxm8HC6SbcGYk4C7yoZ\nv/ZUTi+2J+ilEUkc2pVAevKMB7njVawLEdHsRK0JGpzAhVBIUnS9P1krhiIK1RMy\n9GS/6VIaAdQQl8A8xwHipiQwwNS40zXPx6yYaAi4WI5jfgN+4AM/lhIV4jK7UPhx\n+VVxJ0ccieaO0bURF5YeNZkWq6NNHJ3knvywIfDn1R1OzuxbQiXlkdNKUY5NXr53\nHw94kpNMFoFNck7k32hmelbBqGXwvdy8TOi+wBeZtBlgFLmUfrK4/jwy/ujfzmEA\nKfDveNFBoSK6W2peErGG35gZNI9OXHhthHcgSwpsuAfkm7omWR+XTDKA5mcSuA==\n-----END CERTIFICATE-----\n"

/*
 * @brief PEM-encoded issuer certificate for AWS IoT Just In Time Registration (JITR).
 *
 * @todo If you are using AWS IoT Just in Time Registration (JITR), set this to
 * the issuer (Certificate Authority) certificate of the client certificate above.
 *
 * @note This setting is required by JITR because the issuer is used by the AWS
 * IoT gateway for routing the device's initial request. (The device client
 * certificate must always be sent as well.) For more information about JITR, see:
 *  https://docs.aws.amazon.com/iot/latest/developerguide/jit-provisioning.html,
 *  https://aws.amazon.com/blogs/iot/just-in-time-registration-of-device-certificates-on-aws-iot/.
 *
 * If you're not using JITR, set below to NULL.
 *
 * Must include the PEM header and footer:
 * "-----BEGIN CERTIFICATE-----\n"\
 * "...base64 data...\n"\
 * "-----END CERTIFICATE-----\n"
 */
#define keyJITR_DEVICE_CERTIFICATE_AUTHORITY_PEM ""

/*
 * @brief PEM-encoded client private key.
 *
 * @todo If you are running one of the FreeRTOS demo projects, set this
 * to the private key that will be used for TLS client authentication.
 *
 * @note Must include the PEM header and footer:
 * "-----BEGIN RSA PRIVATE KEY-----\n"\
 * "...base64 data...\n"\
 * "-----END RSA PRIVATE KEY-----\n"
 */
#define keyCLIENT_PRIVATE_KEY_PEM "-----BEGIN RSA PRIVATE KEY-----\nMIIEowIBAAKCAQEAocFCh9DUb/4fI3oo9xJQgqzk7NyIyAnp18mBUlG6P6SXRJAY\nUcEOke2iWN2Z26RnUG4Yj/FUcY/3GwKIt4Bq7WW32lJrxQhnzf7tjIpt+iEt6Z8+\ns6P2xZPuEUyUsoY5ULuU483s3+VzI7+DtNnEt0deiPv8Q+B+gbGsT7I+P/uv0fDk\noHp6IxzNzBBfcPSK9PL0+jqBs3ZDZnHbQiewRuBK39bA2APFBOMzM8AKifXygR+j\nvAZF3qape/pcFBWOK/tQG02HCn97jupkEVu/GPyhIcv37wYPkUXgaql1o08zyEwy\np0pway1K1e/kOVzE4/IENRu8VBRiqeP7f8UATQIDAQABAoIBAHpiD2VU8jZdzc94\n0N/GwpVsHLS9UtwO7BdxBWB0J3eZnz2nzE6mw9BTPF8CIzPUmrp24iyeSea2Jx8P\ndsNn7P760/TiIVntNyTbeX25CuaSDfvRmY4vQzlP6HK8P1EnTtwvYMJO/qaUIt5s\nO0ks7rJA1FzOUppEk1KrTBTsZj7fia/B7hmcJMsQFpdk3AU0b/rkvap903SFAkE3\nZfNKe63jBxwxSxwm1V1PUDECrJHAiFiWNO44o+jr4oakdm3nLQkKIwMVrvvzhE5V\npfU5RWV8WjpmEL4W9h76gWK5AR8JJjt8Dmv8jD/0J4fE5swJkS9wmcJ9U4RP0n7V\nPqodYB0CgYEA0D4oiywxG7FXY7LqoRmSMB6L064ohK/kdYnLPtrgx6Z3tj9oQ+5u\nNfUmB0UB9tZAyMqWVAwmM8yGI55XsN9ExfQrqXtuqbvqr3xU8zQHLTM5g7sRohwV\n6SiA1WCVNIRUeWG7aCrso3O2/r7CggTvZXlult9iCrLojn5nYcnt5u8CgYEAxtnR\nlNMCF/sSmH/cK7X7E4F+/BZX1Og5hUK/fWhCx1BgIQYt0lhSkCEjsWQAeoNHk2QN\nQsHMOVIxpVH+7wiyJBG2rDhKMybN1cOXpNbz+uadho3q5XQmT/sY4CkkWQj+nUdl\nXd/qqvd4aAWfERImMPs5XBsgZgA2X1DPcOQVbIMCgYAVMz7NbGJTf2p2K/DXFdNc\nMr/pfQGDAKUxkiWu8HmR2dC2LR5gTBXMSHjmpI/eoVFXH8jOJa5994Rwe95Rk2lc\n/c60ImzRut/Znb7IQ7O3Vk+0qYbSCinw4r66+mo2PoKbGOgLYtNUkKNArAsBUZ9N\npV8s3PEORciHOTctLXGa4QKBgAejE/aISBtNrEApIPaYzaTJI2xhG0x1AsiIcLxL\nRc1L2/VIvHfIppscerd0ZMRPyG7zt8KpmMNW0ctMo+LgTZ8vAvoIS2k9g0hDc86D\n5ujq9H/XcX8Qf+wwc5sgWWIGA2lc9ZquX9/jEz/Df4FzVf4pl+FetVbViUEN5Hms\neNorAoGBAM0AZj8tzehJMS9QqLqoux4ap4Fwxv4Ew8fwb/fybBFG+LgDEin5fav1\nFt1KMBSnKLv5M4tALN4q3biIydZkpc3+MWIIB8h/YobS5G2cL0A48wplEnOZiIO+\n/LF9ArWhPLFSSgOemBSkiS1LRG7a6rGjF5/RA6kGZFMvIsxqc+oo\n-----END RSA PRIVATE KEY-----\n"

#endif /* AWS_CLIENT_CREDENTIAL_KEYS_H */
