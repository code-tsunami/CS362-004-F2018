import junit.framework.AssertionFailedError;
import junit.framework.TestCase;
import java.util.concurrent.ThreadLocalRandom;

//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!



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