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
#define keyCLIENT_CERTIFICATE_PEM "-----BEGIN CERTIFICATE-----\nMIIDWjCCAkKgAwIBAgIVAOS1jnRDgAs/k6ERYd1FaEXVx72/MA0GCSqGSIb3DQEB\nCwUAME0xSzBJBgNVBAsMQkFtYXpvbiBXZWIgU2VydmljZXMgTz1BbWF6b24uY29t\nIEluYy4gTD1TZWF0dGxlIFNUPVdhc2hpbmd0b24gQz1VUzAeFw0yMDExMDMyMzM0\nMDhaFw00OTEyMzEyMzU5NTlaMB4xHDAaBgNVBAMME0FXUyBJb1QgQ2VydGlmaWNh\ndGUwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQDZc8jMpZluyPMM/Ne9\nxautJTNG2DqoxTx4lIVDuVUs34D3a9A9VqOi9GLr6NU9wn2VnyUwvxq6Wvami47b\n03qLmL2Yd6rU/Ad0UGviR5HE0yRG2jHnTgM6v1mFMUYrQyiyTJXn5FiPSYDdpODA\n8CLOY5OdgjxyJH2y84GUEK+jL5iM3M46XwfjP2/dN0X2ZBEcFIohs3XSdQgAm/YJ\nHYamMZ9AaIc9CSd0iAW+aY4rdr1GgK7o/6SnJbSkcIbgUDpkqfFGPjXZZrJYqREd\nqoRBvjXcuk9MMY5SggB5WnBzR06EIZ2UCrsO6NiP+QN8pFvkWT12UVAUiZ94nOLw\naQwrAgMBAAGjYDBeMB8GA1UdIwQYMBaAFBDJmzmF58ZYSlrzUxg5hBhE27JSMB0G\nA1UdDgQWBBRXoG6fDxZaOorf8oqrl+0kO2SsIjAMBgNVHRMBAf8EAjAAMA4GA1Ud\nDwEB/wQEAwIHgDANBgkqhkiG9w0BAQsFAAOCAQEAc/24M/iBc/btG47xee5KNQEy\ny9gsdNbLbYmI+tJ4Bd9qsgCYbM32cHRLi+bYjFw73ze5gv5zM+Rlaho/VcceubDk\nz8sNFhWw8iMsEEcajYnhDwO5Kr8XuKRIkaFab8DaUoGBJT1KFbVgjjKVmPgJSGYB\nOPg1Kd4koA9+dJrAcKOml5OzOdQTHGUy4if2PM+Y4k3XsxZQfDoljhVDbcXZWzvh\nBxyy7H9/vd5aQJvpeS/97AcAHZEnmfi6zWm6ysWtNmglCt9X7jHhy+JiOezn4Q1V\nWi7QOpr3880O3alPlHQdZB+22Gv3v5NTRmWkH68OnFNA4hH+tGfpnA9q+DX9NQ==\n-----END CERTIFICATE-----\n"

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
#define keyCLIENT_PRIVATE_KEY_PEM "-----BEGIN RSA PRIVATE KEY-----\nMIIEogIBAAKCAQEA2XPIzKWZbsjzDPzXvcWrrSUzRtg6qMU8eJSFQ7lVLN+A92vQ\nPVajovRi6+jVPcJ9lZ8lML8aulr2pouO29N6i5i9mHeq1PwHdFBr4keRxNMkRtox\n504DOr9ZhTFGK0MoskyV5+RYj0mA3aTgwPAizmOTnYI8ciR9svOBlBCvoy+YjNzO\nOl8H4z9v3TdF9mQRHBSKIbN10nUIAJv2CR2GpjGfQGiHPQkndIgFvmmOK3a9RoCu\n6P+kpyW0pHCG4FA6ZKnxRj412WayWKkRHaqEQb413LpPTDGOUoIAeVpwc0dOhCGd\nlAq7DujYj/kDfKRb5Fk9dlFQFImfeJzi8GkMKwIDAQABAoIBAED62IZO9gqlAfxf\nkhijeSnEdA43j0/foLJnr2sNduZx45gMH640tbF8VhMpAI/0DpMne3WVpecKR6p9\nCbOm/ne4rO9i0ynSJmgboCF+QZEPh0ek7ESyi0SC6b1jfBRxfTfKqwEgu1YWIOwa\n2Q7Os5f5KaNnx6hUPzu6iH42fkXE5jDsYOgq2YK6SktoWFjNc/0C9KkBb1upcL93\nu63HvQPEsWxLWNw0FBE4rop+vQXph9DkYJwHm0Go8YScmSJhucU7jX3VvkpSFIcE\na3ka/YfE5uxYIM1FoKsa5cKfFUr92/u8sxCBxzJuqc52ejrcy9DwXfCZmigFUTEA\noL8m/AECgYEA9ajmjRHP8V9R39CVE/GLlKXS9mpiz28nnPExj6NxSayM00T5ijEh\nPjgDMV+ssQEx7kFVZJU+cgdIv3yuIUid3abKFG+JSwHXPiacWJTPE2iZiNQWBixb\nELziu3c4YjyUOi4jIpH8dU9znjHMxM2Bpm6zU5ZmXK0idYsEUpn33O8CgYEA4prv\nVCG2YuMKrGtYG2pquWWke7dxy6eUXfn4r4cXmbAAIKzV0rMOmbCjyXPlwlVEoRR8\noVQQye2ctPpl+1uHU93ODJyFSB9LSTNlk8GpXf0V1+SuJyvicGX+a/FWcuR2Vayt\njhPFLaP7jTqdEokwAdQ745ZoTOYnq7pUkS1Y/IUCgYBqZ/1tD1EVyObq3iskl1SR\nT35gc9ZW6VusNCD2iaIRemcJP/AitoMisxpW8Y0Yol7hR3VYeviwZY1SPAwkqJKQ\npqUTUviR/7se1ZSVHefQDVerl8nuZJoRVu+SqeJHUtwVk1RurfM/UOnQlNuQRz+o\nOnz8cMHn1Kp/ZXa63KwrCwKBgGLtZtxg12H2YpuBRXa6j5ser58/J9PT9ibM0W+3\n12rF9lhNfA+/EfmwruBs03pyhUKZUguQSsANFuO/iTQh8kN/ysugrWMeHlz3rjnC\nSzF4Isgc0pbRRsrxDBCNzMLd0Hd4qlAje2qAc3plg1srPyUdRYQHDsO7msgS0YaL\nuJSNAoGAJCkcMcqElSkeLLORYi8tzKdVLkWlQK16eA6ooLfDuBVDqiYswIDuY7O2\neWWzDCkINwV87W/hFE/EuT9JALdzfTPiK0Hr3kSXTmtAIPQx8lSTfQ1yy+QdT5NE\nYEp8MiBop/tq0TxVElUOQJpqNgolwv2LmtOnyst2nhB3gFNPZmo=\n-----END RSA PRIVATE KEY-----\n"

#endif /* AWS_CLIENT_CREDENTIAL_KEYS_H */
