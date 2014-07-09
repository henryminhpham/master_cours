//
//  ViewController.m
//  LocaliseMoi
//
//  Created by m2sar on 10/01/2014.
//  Copyright (c) 2014 m2sar. All rights reserved.
//

#import "MapViewController.h"

@interface MapViewController ()

@end

@implementation MapViewController

- (id) init {
    self = [super init];
    if(self) {
        CGRect frame = [[UIScreen mainScreen] bounds];
        view = [[MapView alloc] initWithFrame:frame];
        [self setTitle:@"Localisation"];
        isLat = NO;
        isFirst = 0;
        isLng = NO;
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    [self setView:view];
    [view setFromOrientation:[[UIApplication sharedApplication] statusBarOrientation]];
    [[view getTextView] setDelegate:self];
    [view release];
}


- (CellMapContent*) getMapContent {
    return mapContent;
}

- (void) doRequest {
    NSString* value = [view getUrl];
    NSString* clean = [value stringByReplacingOccurrencesOfString:@" " withString:@"%20"];
    if([value length] < 2) {
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"Erreur" message:@"Impossible d'effectuer de recherche sur la chaîne donnée" delegate:nil cancelButtonTitle:@"OK" otherButtonTitles:nil];
        [alert show];
        [alert release];
        [view resetText];
        return;
    }
    NSString* url = [NSString stringWithFormat:@"http://maps.googleapis.com/maps/api/geocode/xml?address=%@&sensor=false", clean];
    
    UILocalNotification *notification = [[UILocalNotification alloc] init];
    [notification setAlertBody:value];
    [[UIApplication sharedApplication] presentLocalNotificationNow:notification];
    
    NSURL* myUrl = [NSURL URLWithString:[NSString stringWithFormat:url, value]];
    NSURLRequest* request = [[NSURLRequest alloc] initWithURL:myUrl cachePolicy:NSURLRequestReloadIgnoringCacheData timeoutInterval:30];
    [[NSURLConnection alloc] initWithRequest:request delegate:self startImmediately:YES];
    webData = [[NSMutableData alloc] init];
    mapContent = [[CellMapContent alloc] init];
    [mapContent setLabel:value];
}

- (void) connection:(NSURLConnection *)connection didReceiveData:(NSData *)data {
    [webData appendData:data];
}

- (void) connection:(NSURLConnection *)connection didFailWithError:(NSError *)error {
    UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"Erreur" message:[error localizedDescription] delegate:nil cancelButtonTitle:@"OK" otherButtonTitles:nil];
    [alert show];
    [alert release];
}

- (void) connectionDidFinishLoading:(NSURLConnection *)connection {
    NSXMLParser* parser = [[NSXMLParser alloc] initWithData:webData];
    [parser setDelegate:self];
    BOOL resParse = [parser parse];
    if(resParse == NO) {
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"Erreur" message:@"Impossible de parser le document récupéré" delegate:nil cancelButtonTitle:@"OK" otherButtonTitles:nil];
        [alert show];
        [alert release];
    }
    [webData release];
    [connection release];
}

- (void) parserDidEndDocument:(NSXMLParser *)parser {
    [parser release];
    isLat = NO;
    isLng = NO;
    isFirst = 0;
    [view makePosition:[mapContent latitude] :[mapContent longitude]];
    [[NSNotificationCenter defaultCenter] postNotificationName:@"LocaliseMoi" object:self];
}

- (void) parser:(NSXMLParser *)parser didStartElement:(NSString *)elementName namespaceURI:(NSString *)namespaceURI qualifiedName:(NSString *)qName attributes:(NSDictionary *)attributeDict {
     if([elementName isEqualToString:@"lng"] && isFirst < 2) {
        isLng = YES;
        isFirst++;
    } else if([elementName isEqualToString:@"lat"] && isFirst < 2) {
        isLat = YES;
        isFirst++;
    }
}

- (void) parser:(NSXMLParser *)parser foundCharacters:(NSString *)string {
    if(isFirst <= 2 && isLng) {
        [mapContent setLongitude:[string doubleValue]];
        isLng = NO;
    } else if(isFirst <= 2 && isLat) {
        [mapContent setLatitude:[string doubleValue]];
        isLat = NO;
    }
}

- (BOOL) textView:(UITextView *)textView shouldChangeTextInRange:(NSRange)range replacementText:(NSString *)t {
    if([t isEqualToString:@"\n"]){
        [self doRequest];
        return NO;
    }
    return YES;
}

- (void) makePosition: (CellMapContent*) content {
    [view makePosition:[content latitude] :[content longitude]];
}

- (void) showNavigationButton:(UIBarButtonItem*)b {
    [[self navigationItem] setLeftBarButtonItem:b];
}

- (void) hideNavigationButton {
    [[self navigationItem] setLeftBarButtonItem:nil];
}

- (BOOL) shouldAutorotate {
    return YES;
}

-(void) willRotateToInterfaceOrientation:(UIInterfaceOrientation)o
                                duration:(NSTimeInterval)duration{
    [view setFromOrientation:o];
}

- (void) didRotateToInterfaceOrientation:(UIInterfaceOrientation)o{
    [view setFromOrientation:o];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
}

@end
