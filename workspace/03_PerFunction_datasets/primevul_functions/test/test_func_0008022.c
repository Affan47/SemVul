TEST("Test exceptions")
{

    test_urldecode("Hello%20World%21%40%", "Hello World!@%");


    test_urldecode("Hello%20World%21%40%2", "Hello World!@%2");


    test_urldecode("Hello%20World%21%40%%", "Hello World!@%%");


    test_urldecode("Hello%20World%21%40%%%", "Hello World!@%%%");


    test_urldecode("Hello%20World%21%40%%%%", "Hello World!@%%%%");


    test_urldecode("Hello%20World%21%40%%%61%%", "Hello World!@%%a%%");


    test_urldecode("Hello%20World%21%40%1Q", "Hello World!@%1Q");
}
