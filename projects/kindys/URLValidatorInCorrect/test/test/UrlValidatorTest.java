import junit.framework.AssertionFailedError;
import junit.framework.TestCase;

import java.util.concurrent.ThreadLocalRandom;

public class UrlValidatorTest extends TestCase {
   private UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

   // NOTE - These are reused from the valid test code, as they simply represent fairly
   // comprehensive pieces of URL generation and it is separate from the actual test logic.
   private static final ResultPair[] schemes = {new ResultPair("http://", true),
           new ResultPair("ftp://", true),
           new ResultPair("h3t://", true),
           new ResultPair("3ht://", false),
           new ResultPair("http:/", false),
           new ResultPair("http:", false),
           new ResultPair("http/", false),
           new ResultPair("://", false),
           new ResultPair("", true)};

	private static final ResultPair[] authorities = {new ResultPair("www.google.com", true),
          new ResultPair("go.com", true),
          new ResultPair("go.au", true),
          new ResultPair("0.0.0.0", true),
          new ResultPair("255.255.255.255", true),
          new ResultPair("256.256.256.256", false),
          new ResultPair("255.com", true),
          new ResultPair("1.2.3.4.5", false),
          new ResultPair("1.2.3.4.", false),
          new ResultPair("1.2.3", false),
          new ResultPair(".1.2.3.4", false),
          new ResultPair("go.a", false),
          new ResultPair("go.a1a", false),
          new ResultPair("go.1aa", false),
          new ResultPair("aaa.", false),
          new ResultPair(".aaa", false),
          new ResultPair("aaa", false),
          new ResultPair("", false)
	};
	
	private static final ResultPair[] ports = {new ResultPair(":80", true),
         new ResultPair(":65535", true),
         new ResultPair(":0", true),
         new ResultPair("", true),
         new ResultPair(":-1", false),
         new ResultPair(":65636",false),
         new ResultPair(":65a", false)
	};
	
	private static final ResultPair[] paths = {new ResultPair("/test1", true),
          new ResultPair("/t123", true),
          new ResultPair("/$23", true),
          new ResultPair("/..", false),
          new ResultPair("/../", false),
          new ResultPair("/test1/", true),
          new ResultPair("", true),
          new ResultPair("/test1/file", true),
          new ResultPair("/..//file", false),
          new ResultPair("/test1//file", false)
	};
	
   
   public UrlValidatorTest(String testName) {
      super(testName);
   }
   
   // Method to abstract returning a random int in a specified range. Source:
   // https://stackoverflow.com/questions/363681/how-do-i-generate-random-integers-within-a-specific-range-in-java
   private static int rand(int min, int max) {
       int val = ThreadLocalRandom.current().nextInt(min, max+1);
       return val;
   }


   // MANUAL TESTING
   
   public void testManualTest()
   {
       System.out.println("\nManual Testing - expect true");

       // examples taken from places online and randomly generated
       String[] validFormatUrls = {
               "https://websitebuilders.com",
               "https://www.facebook.com/Learn-the-Net-330002341216",
               "http://europa.eu/admin/login",
               "http://europa.eu/admin",
               "http://europa.eu/admin/",
               "ftp://aeneas.mit.edu/",
               "https://en.wikipedia.org/wiki/Internet#Terminology",
               "https://oregonstate.instructure.com/courses/1692912/assignments",
               "ftp://0.0.0.0:1024/admin/login",
               "ftp://www.google.com:65535/path#index",
               "www.google.com/admin/",
               "h3t://oregonstate.edu/admin/login?admin=false",
               "h3t://255.255.255.255:65535/z456",
               "http://www.google.com:1024/admin/",
               "https://0.0.0.0/z456",
               "https://www.google.com:65535?q=Test%20URL-encoded%20stuff",
               "docs.python.org:65535/path#index",
               "http://255.com:65535/admin/",
               "http://www.google.com/path#index",
               "ftp://oregonstate.edu/path#index",
               "http://255.com:1024/admin/login?admin=false",
               "europa.eu/admin/login?admin=false",
               "ftp://0.0.0.0:1024/admin/login?admin=false",
               "h3t://oregonstate.edu:65535/admin/login",
               "ftp://0.0.0.0:1024/admin/login?admin=false",
               "ftp://oregonstate.edu:1024/admin/login?admin=false",
               "https://docs.python.org:65535/admin/login?admin=false",
               "www.google.com/456",
               "https://europa.eu/456",
               "http://0.0.0.0/z456",
               "h3t://255.com:65535/path#index",
               "h3t://oregonstate.edu/admin/login?admin=false",
               "oregonstate.edu/z456",
               "https://255.com:1024?q=Test%20URL-encoded%20stuff",
               "www.google.com/path#index",
               "europa.eu:1024/456",
               "ftp://255.255.255.255:1024/admin/login?admin=false",
               "docs.python.org:65535/z456",
               "https://www.google.com:1024/z456",
               "ftp://oregonstate.edu:65535/admin/login?admin=false",
               "http://oregonstate.edu:1024",
               "h3t://oregonstate.edu:1024/admin/",
               "255.255.255.255:1024/z456",
               "ftp://255.255.255.255:1024/admin/",
               "h3t://255.com:1024/admin/login?admin=false",
               "h3t://docs.python.org:1024/admin/login?admin=false",
               "h3t://docs.python.org/path#index",
               "h3t://255.255.255.255?q=Test%20URL-encoded%20stuff",
               "https://www.google.com:65535/z456",
               "h3t://0.0.0.0:1024/path#index",
               "http://oregonstate.edu:1024/path#index",
               "http://europa.eu:1024/admin/login",
               "europa.eu/admin/",
               "docs.python.org:1024/admin/",
               "http://www.google.com:65535?q=Test%20URL-encoded%20stuff",
               "h3t://www.google.com",
               "ftp://255.255.255.255",
               "oregonstate.edu/456",
               "ftp://255.com:65535/admin/login?admin=false",
               "ftp://europa.eu/path#index",
               "http://oregonstate.edu:1024/admin/",
               "http://255.255.255.255/admin/",
               "http://docs.python.org/admin/login",
               "h3t://docs.python.org:1024",
               "h3t://docs.python.org:65535/456",
               "h3t://www.google.com:1024/path#index",
               "ftp://255.255.255.255:65535/admin/login",
               "ftp://europa.eu:65535/path#index",
               "ftp://docs.python.org/path#index",
               "https://www.google.com:65535",
               "h3t://www.google.com?q=Test%20URL-encoded%20stuff",
               "http://0.0.0.0:1024/admin/login?admin=false",
               "h3t://docs.python.org:65535/admin/login?admin=false",
               "https://0.0.0.0:65535/z456",
               "ftp://0.0.0.0:65535/admin/login",
               "ftp://oregonstate.edu:1024?q=Test%20URL-encoded%20stuff",
               "ftp://www.google.com:1024/admin/",
               "ftp://255.255.255.255/456",
               "h3t://0.0.0.0:1024/admin/login?admin=false",
               "https://www.google.com:65535/admin/login?admin=false",
               "http://0.0.0.0/admin/login",
               "ftp://255.255.255.255:1024/z456",
               "http://255.com:1024",
               "h3t://docs.python.org:1024/z456",
               "h3t://docs.python.org/admin/",
               "docs.python.org:65535/admin/login",
               "h3t://255.255.255.255",
               "www.google.com/456",
               "h3t://oregonstate.edu:1024/456",
               "http://255.com:65535/admin/login",
               "http://docs.python.org:65535?q=Test%20URL-encoded%20stuff",
               "ftp://0.0.0.0:65535/z456",
               "https://255.255.255.255:65535/admin/login",
               "http://255.com:1024/path#index",
               "https://255.255.255.255:1024/admin/login?admin=false",
               "h3t://255.255.255.255:1024/456",
               "europa.eu:1024?q=Test%20URL-encoded%20stuff",
               "ftp://www.google.com",
               "http://255.255.255.255:65535/admin/login",
               "h3t://europa.eu:1024/admin/login",
               "http://255.255.255.255:1024/path#index",
               "www.google.com/admin/"
       };
       System.out.println("\nManual Testing - expect true");
       for (String s: validFormatUrls) {
           printedAssertTrue(s);
       }

       String[] invalidFormatUrls = {
               "3ht://255.com:65a/admin/login",
               "https://nodomain/admin/login",
               "http://www.google.com:65536/../",
               "oregonstate.edu:65536/admin/login",
               "h3t://1.2.3.4.5:65536/../",
               "site.z9:65535/..//login",
               "://1.2.3.4.:65536/../",
               "http:/docs.python.org:65535/..//login",
               "http:/site.z9:1024/../",
               "https://256.255.255.255?q=Test%20URL-encoded%20stuff",
               "http:256.255.255.255:65a/z456",
               "1.2.3.4.5/456",
               "h3t://256.255.255.255:65536/../",
               "http:/1.2.3.4.:1024/z456",
               "http:/oregonstate.edu:-1/..//login",
               "http:/.1.2.3.4:-1/admin/login?admin=false",
               "http:/.1.2.3.4:65535/admin/login",
               "256.255.255.255:65536/admin//login",
               "http:/1.2.3.4.5:1024/456",
               "http://oregonstate.edu/..",
               "ftp://1.2.3.4.5:65535/../",
               "http/1.2.3.4.5:-1/../",
               "http://oregonstate.edu:65a/456",
               "h3t://1.2.3:1024/../",
               ":1024/admin//login",
               "ftp://nodomain/z456",
               "http:256.255.255.255:65536/../",
               "https://256.255.255.255:65536/path#index",
               "https://1.2.3:-1/admin/",
               "http:site.z9:1024/..//login",
               "http/site.z9:-1/456",
               "256.255.255.255/admin/login",
               "http:/nodomain:1024/456",
               "http:1.2.3:65a?q=Test%20URL-encoded%20stuff",
               "https://www.google.com:65536/../",
               "http:/256.255.255.255:-1/admin//login",
               "http://site.z9?q=Test%20URL-encoded%20stuff",
               "oregonstate.edu/..",
               "site.z9:65535/path#index",
               ".1.2.3.4:65536/path#index",
               "http:www.google.com/admin/login",
               "http:/1.2.3.4.:1024/admin/login?admin=false",
               "https://:65536/admin/login",
               "http:/oregonstate.edu:65a/../",
               "http://1.2.3.4.:65536/..",
               "h3t://0.0.0.0:65535/../",
               "ftp://256.255.255.255:65536/456",
               "http/1.2.3.4.:1024/z456",
               "http/1.2.3.4.:1024/..",
               "https://1.2.3:-1/admin/",
               "3ht://site.z9:1024/admin/",
               "h3t://:65535/../",
               "://0.0.0.0:1024/../",
               "http://1.2.3.4.5/..",
               "http/docs.python.org:65a/admin/",
               "ftp://site.z9:-1/../",
               "http/256.255.255.255:-1/../",
               "3ht://europa.eu:-1?q=Test%20URL-encoded%20stuff",
               "http://.1.2.3.4:65535/path#index",
               "h3t://:65535/456",
               "h3t://1.2.3/..",
               "http:/:-1/..//login",
               "http/site.z9:65536/admin/",
               "http/1.2.3:65535/admin/login?admin=false",
               "nodomain:-1/..",
               "http:1.2.3.4.:65a/admin/login",
               "ftp://docs.python.org/..//login",
               "3ht://.1.2.3.4:1024/../",
               "http://.1.2.3.4:65535/admin//login",
               "255.com:65a/..",
               "1.2.3.4.5?q=Test%20URL-encoded%20stuff",
               "http:site.z9:65a/../",
               "site.z9:65a/admin/",
               "h3t://1.2.3.4.:65535",
               "http:/256.255.255.255:65535/..",
               "://site.z9:1024/456",
               "oregonstate.edu:65a",
               "http/europa.eu:65a",
               ".1.2.3.4/admin/",
               "https://1.2.3.4.5:65536/z456",
               "http:0.0.0.0/admin/login",
               "http:/www.google.com:65a/admin//login",
               "3ht://site.z9:-1/admin/login?admin=false",
               "http:255.com:1024/admin//login",
               "http/www.google.com:-1/../",
               "http:?q=Test%20URL-encoded%20stuff",
               "http:/docs.python.org:65535/456",
               "https://1.2.3.4.:65535/../",
               "3ht://.1.2.3.4/../",
               "http:docs.python.org:-1/path#index",
               "http:/www.google.com:65536/..//login",
               "http:/256.255.255.255:65536/admin//login",
               "1.2.3.4.5:65a?q=Test%20URL-encoded%20stuff",
               "h3t://255.com:65536/admin/",
               "://1.2.3.4.5/path#index",
               "https://1.2.3:65a/../",
               "http:/oregonstate.edu:1024",
               ".1.2.3.4:65535/admin/login",
               "ftp://.1.2.3.4:65535/../",
               "http:docs.python.org:-1/path#index"
       };

       System.out.println("\nManual Testing - expect false");
       for (String s: invalidFormatUrls) {
           printedAssertTrue(s);
       }

   }

   public void printedAssertFalse(String url) {
      try {
         boolean result = urlVal.isValid(url);
         if (result) {
            System.out.println("TESTING " + url + " FAILED: expected FALSE but received TRUE");
         } else {
            System.out.println("TESTING " + url + " SUCCEEDED: received FALSE");
         }
      } catch(Error e) {
         System.out.println("TESTING " + url + " FAILED: received ERROR");
      }
   }

   public void printedAssertTrue(String message) {
      try {
         boolean result = urlVal.isValid(message);
         if (result) {
            System.out.println("TESTING " + message + " SUCCEEDED: received TRUE");
         } else {
            System.out.println("TESTING " + message + " FAILED: expected TRUE but received FALSE");
         }
      } catch(Error e) {
         System.out.println("TESTING " + message + " FAILED: received ERROR");
      }
   }

   
   // PARTITION TESTING 
   
   public void testSchemePartition_Succeed() {
      System.out.println("\nScheme Partition - expect true");

      printedAssertTrue("http://www.google.com");
      printedAssertTrue("www.google.com");
      printedAssertTrue("ftp://www.google.com");
      printedAssertTrue("h3t://www.google.com");
   }

   public void testSchemePartition_Fail() {
      System.out.println("\nScheme Partition - expect false");

      printedAssertFalse("3ht://www.google.com");
      printedAssertFalse("http:/www.google.com");
      printedAssertFalse("http:www.google.com");
      printedAssertFalse("://www.google.com");
   }
   //You need to create more test cases for your Partitions if you need to

   public void testAuthorityPartition_Succeed() {
      System.out.println("\nAuthority Partition - expect true");

      printedAssertTrue("http://www.google.com");
      printedAssertTrue("http://go.com");
      printedAssertTrue("http://google.au");
      printedAssertTrue("http://0.0.0.0");
      printedAssertTrue("http://255.255.255.255");
   }

   public void testAuthorityPartition_Fail() {
      System.out.println("\nAuthority Partition - expect false");

      printedAssertFalse("http://256.256.256.256");
      printedAssertFalse("http://255.com");
      printedAssertFalse("http://1.2.3.4.5");
      printedAssertFalse("http://go.a");
   }
   //You need to create more test cases for your Partitions if you need to

   public void testPartitionWithHTTP() {
      System.out.println("\nHTTP Partition - all URLS have http in them.");

      printedAssertTrue("http://www.google.com");
      printedAssertFalse("http:/go.com");
      printedAssertFalse("http:/");
      printedAssertFalse("http:/absdfs");
   }

   public void testPartitionWithoutHTTP(){

      System.out.println("\nHTTP Partition - no URLS have HTTP");

      printedAssertTrue("ftp://www.google.com");
      printedAssertTrue("abc.com");
      printedAssertTrue("www.yahoo.edu");
   }

   // PROGRAMMING BASED TESTING
   
   public void testValidResultPair() {
	   ResultPair validTest = new ResultPair("http://", true);
	   try {
		   assertTrue(validTest.valid);
	   } catch (AssertionFailedError e) {
		   System.out.println("TESTING valid ResultPair FAILED: expected valid but was invalid.");
	   }
   }
   
   public void testInvalidResultPair() {
	   ResultPair invalidTest = new ResultPair("http/:", false);
	   try {
		   assertTrue(!invalidTest.valid);
	   } catch (AssertionFailedError e) {
		   System.out.println("TESTING invalid ResultPair FAILED: expected invalid but was valid.");
	   }
   }
   
   public void testIsValid() {
	   System.out.println("\nProgramming based random URL tests");
	   
	   int schemeIndex, authorityIndex, portIndex, pathIndex; 
	   String testUrl;
		
	   for(int i = 0; i < 1000; i++) {
		   // Randomly create URL scheme, authority, port, and path
		   schemeIndex = rand(0, schemes.length - 1);
		   authorityIndex = rand(0, authorities.length - 1);
		   portIndex = rand(0, ports.length - 1);
		   pathIndex = rand(0, paths.length - 1);
		   
		   // Build test URL from random pieces generated above.
		   testUrl = schemes[schemeIndex].item + authorities[authorityIndex].item
				   + ports[portIndex].item + paths[pathIndex].item;
			
		   // NOTE - due to the bug in ResultPair, "valid" url parts are actually invalid.
		   // Thus I would expect a high rate of failures here until that bug is fixed.
		   if (schemes[schemeIndex].valid || authorities[authorityIndex].valid
				   || ports[portIndex].valid || paths[pathIndex].valid) {
			   // Should be a valid URL
			   printedAssertTrue(testUrl);
		   }
		   else {
			   // Should be an invalid URL
			   printedAssertFalse(testUrl);
		   }
	   }
   }
}