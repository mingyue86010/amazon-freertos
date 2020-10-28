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
#define keyCLIENT_CERTIFICATE_PEM "-----BEGIN CERTIFICATE-----\nMIIDWjCCAkKgAwIBAgIVAK6yJI0z8Wse5B3G+NO01vmlZP5DMA0GCSqGSIb3DQEB\nCwUAME0xSzBJBgNVBAsMQkFtYXpvbiBXZWIgU2VydmljZXMgTz1BbWF6b24uY29t\nIEluYy4gTD1TZWF0dGxlIFNUPVdhc2hpbmd0b24gQz1VUzAeFw0yMDEwMjcyMTMw\nMTZaFw00OTEyMzEyMzU5NTlaMB4xHDAaBgNVBAMME0FXUyBJb1QgQ2VydGlmaWNh\ndGUwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQC3sG6ScFZdDbhMj+Fi\nNJ1SPIdXyZbAj+ZY1Su6RcezhD2SsRMcIDKHAQj6RdhfTA9NKie1+P0sAMkYXvO3\nj0cfGeGgduFmarA049wqbk0mMpXb1NJnABwAmuylsYAT7U8LJN9VducH+KS8CEmo\niCxjlP0NOIkdnqIAEGB4aLENvWyEexwFU+a8v6hgwLx2LMO3k+jZPKZkSFjwx5hA\n3RwWGCor4KyBwtUNyqiSBmpP/EGNVzsgtuv0mZ2zExF81WHr1vK09qlR2okMmmwg\n4iNUnBMRxsmahXXhpK/PsbFFWtngD9ul5QerhALwQKlJE0MMyEBU2tuM4FD7Apkw\nDtuzAgMBAAGjYDBeMB8GA1UdIwQYMBaAFKaSM9+8I4oWVTMGTD8JJMctP1l3MB0G\nA1UdDgQWBBQwgKruKKYW9RDJzryCrFTKYVxbUDAMBgNVHRMBAf8EAjAAMA4GA1Ud\nDwEB/wQEAwIHgDANBgkqhkiG9w0BAQsFAAOCAQEASKGob6Pvw3Cua885XhCALoCP\nvZghWBsUMkVTAznNemjM9JUJ79Nc9Zx9gbQnU9Vg96Id/TpXkrXBp8FMNCbZ4tVR\n9UHhv7PeVxEACIRPEUffD/uULz19NyU0X4QrotmevSaMKxFAEhJyFwHTj8uqMdzw\nSwmqN967pbJZw+Ju7/shGVtojAW83GfNYFgxa9Qw5ct+SwAlSMglmEFazOdm3niV\nkfQ0B7w/pL+QNLW8sGweKz3uFN0REoxhbi6TRAHyNgBoj9SDI7+iNeOZu/EsGPTl\nJmzBoTeYYChiIpxqHdVrlKkID+MkMVOQ1iIFqmYQdYMIGGjtOmJCgPOj1UKcTg==\n-----END CERTIFICATE-----\n"

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
#define keyCLIENT_PRIVATE_KEY_PEM "-----BEGIN RSA PRIVATE KEY-----\nMIIEpQIBAAKCAQEAt7BuknBWXQ24TI/hYjSdUjyHV8mWwI/mWNUrukXHs4Q9krET\nHCAyhwEI+kXYX0wPTSontfj9LADJGF7zt49HHxnhoHbhZmqwNOPcKm5NJjKV29TS\nZwAcAJrspbGAE+1PCyTfVXbnB/ikvAhJqIgsY5T9DTiJHZ6iABBgeGixDb1shHsc\nBVPmvL+oYMC8dizDt5Po2TymZEhY8MeYQN0cFhgqK+CsgcLVDcqokgZqT/xBjVc7\nILbr9JmdsxMRfNVh69bytPapUdqJDJpsIOIjVJwTEcbJmoV14aSvz7GxRVrZ4A/b\npeUHq4QC8ECpSRNDDMhAVNrbjOBQ+wKZMA7bswIDAQABAoIBAQCubbrCEizgljux\ncFuM3vuZcOLwqPwfhUYuitbIPqUhQe0aVE4aQjTY4FG/Hv4VmGtbUjF9aqA23dQX\n8Wqrn0HhNbl8oAbwM1V6E/oozK80G4sUwma96mus43De8sv1oD6UDYKKbKt8dU8x\nQwl3IUBNm9gkatBBsTaSqvqAvKGMsfzYRVAoohCtBPVKxTy5zM6CRpXfkr79nPOS\n0k4v/Y5zuevcwAsKJg4Xd3mt44yhcoUiuwMVigiczJ5psEtgJQlFW7xieSDQxMv6\n1eJt9s4+yrdcgzdONwvdosFfF8lHkr9Dd/h+O5rmQumEYWD+i3eHRImEGOBdpOj5\nHfbvSgnRAoGBAN4uCJvm2CAKl37Hz/gZPkJBQxdjeUvq6lB7KypecVgm2Sh+JhPh\nm6NKnXTjrw9bI6E1gVJPVGHs47DDziyjy8g0tdz5fmjb3ijqsDmyMAJwqWdF+I6l\n6ul4qPOiChiH+c1aH3auOkgX53aQ/1ZSlv+ACJ9FXVVQey8ABqW2Mo3JAoGBANOm\nfAJgJtNTAeBNimcg9B2H4marxqAgtB8Czks/OFkWYp6Uc40xdNqB2+JYkGZzI/fY\nk9V5PzxiDEGXOTDIVa7yr35lruQmC1RS7KwasyXVHVL3eAKzWk509aJ1/b/x2xhe\nkSthdZ76Ioc/3nkuruKcRM+iyZx4xNH0cJMksGubAoGBAKvw+Byes5doWwF0ZM/d\nyT7A/sj05IQKEreh+i/Z0uGjft9FcPZl3Gqsbdpt8aZyo8o4fBJU7jqydyru/Xmy\ncRxJHo0aT+eab/0+Uo70BQ9+XLtdfRP39yojhKy3NBTz9jAjlMHl55ivVyN85v3J\nAK5OSV3o8mf51rryzDImJE1xAoGBAIMrIp+2R1mgkAEbDTNs0N2cYUuQGcETg43U\nh1VLEPjlTqlJB3PxuqHQ6R0WFifoI9pudvBN/ErH2SCtP9xjy/ZooSqMih8LFOpl\nmhfvVCeWNF4+0DmcPdNx2Omehmx2z3oC4aUo+WRVUSDRDGe97tSyVFL6aEh48EHO\nZBZNHqkRAoGAC6gM3xHB2q8moiwoV2cnQ1tCsEZ/RFOlb7CKNKjlXLawLo4ndqii\nZGVKiCP7ZOUl+KbO2zvAdhDjs5LXJB8SK0igTjB4uP1xzqaGeDThwt/hIG2+KRrL\nzf1xk9I0YHb7eM3SulADW56vMjqjKVpX4h4mtPjy+qHiXGzakn6VdfM=\n-----END RSA PRIVATE KEY-----\n"

#endif /* AWS_CLIENT_CREDENTIAL_KEYS_H */
