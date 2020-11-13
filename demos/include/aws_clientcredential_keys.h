/*
 * FreeRTOS V202011.00
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

/*
 ****************************************************************************
 * NOTE!
 * This file is for ease of demonstration only.  Secret information should not
 * be pasted into the header file in production devices.  Do not paste
 * production secrets here!  Production devices should store secrets such as
 * private keys securely, such as within a secure element.  See our examples that
 * demonstrate how to use the PKCS #11 API for secure keys access.
 ****************************************************************************
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
#define keyCLIENT_CERTIFICATE_PEM "-----BEGIN CERTIFICATE-----\nMIIDWjCCAkKgAwIBAgIVAJe0udrB0XcVd0gzBkjyOMtdRf7GMA0GCSqGSIb3DQEB\nCwUAME0xSzBJBgNVBAsMQkFtYXpvbiBXZWIgU2VydmljZXMgTz1BbWF6b24uY29t\nIEluYy4gTD1TZWF0dGxlIFNUPVdhc2hpbmd0b24gQz1VUzAeFw0yMDExMTMwOTIz\nNTNaFw00OTEyMzEyMzU5NTlaMB4xHDAaBgNVBAMME0FXUyBJb1QgQ2VydGlmaWNh\ndGUwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQCo7borQ8MDukWbfae3\nLxqjXcUd15Yw5rh+ljStWGcVF6Ye0B4QgvBEO7n2694A0vIQNOjHD9t3oyvTeH7m\ndYxejI/uvUXLGeoHlMxDUx0yK8gxOBI+sU1nSCCvWfUyoB25y8jj6a5OsKf/1Lhk\n4UpSznYoHSCBzja1h4Uv+cHwnJuqeVX50/FwMVwXOga1e0ORnF1SAYGx55dXmD5k\nNIt4WJb9E+o77J+fgOGl+Z2JipILZzTvVupWf4CqTUHtCzT8sotUYy2oYVcpqObF\ndzWSv9qsy/3qg3PxQQ/RX4g2EGK4wrC8e3bEy6/ZmrutHfrN+C6+8VsbMhjGg8Fd\n6qKvAgMBAAGjYDBeMB8GA1UdIwQYMBaAFE4YG0mn197yGCzNnsv1GipZI3U6MB0G\nA1UdDgQWBBS3WbpNWMthUFBrS95hjD1zVk0uNzAMBgNVHRMBAf8EAjAAMA4GA1Ud\nDwEB/wQEAwIHgDANBgkqhkiG9w0BAQsFAAOCAQEAW3m5oBIIgqAdISM3iZURYWip\n4Wc6tww71ieUqJ7nxirjT4Y50saEsC2Mwkqh7DQ0UhH4O2CZx954EBTcni6nezpS\nvXM+p9W4V158wUVibm35XN1vC1L5E/ZZr4T+gYuA7jowC/rH+ZTe71FJRm6E5zTA\nn6zGHQuhogrZYNSOTWhjSG/eIOSgwmkJgb8BKJIETAMSClDQdb52x59YEaxnvzEI\nT3ePdwQ80Wovf6OyJUuBtgsews2ntQJlMze+msbpZa5LvCwvI82rJwSGPjinEPEx\ni8+6ePUaJJr4NN+DCRjbHafk2N30RGuHdqz7x/VImsBM7/BxsRtmbqijLpJhfw==\n-----END CERTIFICATE-----\n"

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
 * Please note pasting a key into the header file in this manner is for
 * convenience of demonstration only and should not be done in production.
 * Never past a production private key here!.  Production devices should
 * store keys securely, such as within a secure element.  Additionally,
 * we provide the corePKCS library that further enhances security by
 * enabling keys to be used without exposing them to software.
 *
 * @note Must include the PEM header and footer:
 * "-----BEGIN RSA PRIVATE KEY-----\n"\
 * "...base64 data...\n"\
 * "-----END RSA PRIVATE KEY-----\n"
 */
#define keyCLIENT_PRIVATE_KEY_PEM "-----BEGIN RSA PRIVATE KEY-----\nMIIEpQIBAAKCAQEAqO26K0PDA7pFm32nty8ao13FHdeWMOa4fpY0rVhnFRemHtAe\nEILwRDu59uveANLyEDToxw/bd6Mr03h+5nWMXoyP7r1FyxnqB5TMQ1MdMivIMTgS\nPrFNZ0ggr1n1MqAducvI4+muTrCn/9S4ZOFKUs52KB0ggc42tYeFL/nB8JybqnlV\n+dPxcDFcFzoGtXtDkZxdUgGBseeXV5g+ZDSLeFiW/RPqO+yfn4DhpfmdiYqSC2c0\n71bqVn+Aqk1B7Qs0/LKLVGMtqGFXKajmxXc1kr/arMv96oNz8UEP0V+INhBiuMKw\nvHt2xMuv2Zq7rR36zfguvvFbGzIYxoPBXeqirwIDAQABAoIBAQCgD8iTj/wq/wdP\nYotUnfQ+kO3h7dEoeqSbhRVanmXl7WeA0K9786VW8cSt+yV6YGXuB0P8wcCwplIz\naHvNP9oGCGekzYBhBifikRHOROVoEWX5hOh8sKDn2Mbnf3Q+SMqBrl6l3VhExUwZ\nsuQY6gLzXR9FuPuBIvRhoowHPj6ODTtwDIsPvR3AT1dMjGiWyujxK8YPect+dvjG\nap0JqUjBAzDRe/dTS9cbVW9V7VQ+8KD6AEY0Spoj8lFyTwrMqwT3k4J4DUMBy49t\nsvopLplYL8/2y1W+AggRaimzZUj6GcvokEi4mvVybIRNihfOI+CUlpWpJvLH9o/i\nQFNHVrNhAoGBANfycMMvwbj+JgWMgn7Cu13K51sUHKEZCA/rxiRAxAJQRQV5Upcl\nOMEp3uYsRpBvhIKCf16HTrJ+YeXDI99e8zL4OGv+5xwSSiLTmclRmjZu636CRnY7\nB7qoO9ZX4wQPL7E4dsCmtZeMEnw447LxQBuYJ8khan1qIQulYkLSVSlRAoGBAMhC\nxEc6v7WH98Hk9ROWZ+PH0TTN4UUrrSiFl+9JhMBOptPn9Jb0G/3LZp1H+FfDvy1m\nehXVh1gs4/pfA/a/IObcDZuLhknQX5VtEMTO5BCQGJzlebEewcD2uXadQQR/pnQf\nZxzbVBJtNUvxSxhh2OfFWW0qNRpjiTE098R5UAv/AoGAfCq/4cts9WTVEe23/xET\nURvhKYKH762H8Deeh6vhyH7FIR+geJ4DYzYjH3An5tbod253tC/S9VksC0PINaDP\n7+e/8YDw/Dgb/qhyzcopBNGEgQqBX2wTxqUDOvzv4J6mypzv01hII+p7mofPjU2g\nkf1MKx8WryQ9+gdPV6K/KvECgYEAp1FBdNHdAurLUjDdorPzsRht7tRk9sn7LvQP\ncVnXlGUidcJDVSw3huC+p4JON+XQgToxnrR9FGrNP47LXQlrj/cjV2ZHmLyEX/B0\nJjtFyaDbL5t7BUVRVMvPQQ86F2wfwr3KBQ4rPAoKkZzUxVZbR6pXgSHWpGmtYnOC\n36EMBDkCgYEApJFVKMLEKsZ5kKlv9nT3YzQ+7qaTcHOE4wiztg7bomV1TViFVWX0\nTwmI9LBtNhLjrlIwXAQsT7yuwogvTUa4jqHuVwAhNG515aJY7vgBpXQalhdLCXE6\nBub0oc97Zfv9w3kdTsLJ/gav1tFny90GUJ/BF/LnYL6zb7laoijvUL4=\n-----END RSA PRIVATE KEY-----\n"

#endif /* AWS_CLIENT_CREDENTIAL_KEYS_H */
