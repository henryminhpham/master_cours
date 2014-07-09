#import "View.h"

@implementation View

const int DEFAULT_IPAD_X = 20;
const int DEFAULT_IPAD_Y = 20;
const int DEFAULT_IPHONE_X = 10;
const int DEFAULT_IPHONE_Y = 10;

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    isIpad = [[UIDevice currentDevice] userInterfaceIdiom] != UIUserInterfaceIdiomPhone;
    if (self) {
        background = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"isouvenir-elements/fond-2048x2048.jpg"]];
        [self addSubview:background];
        [background release];
        
        myframe = frame;
        if (isIpad) {
            x_origin = DEFAULT_IPAD_X;
            y_origin = DEFAULT_IPAD_Y;
            rapport = 2;
        } else {
            x_origin = DEFAULT_IPHONE_X;
            y_origin = DEFAULT_IPHONE_Y;
            rapport = 1;
        }
        
        width = frame.size.width;
        heigth = frame.size.height;
        
        contact = [UIButton buttonWithType:UIButtonTypeSystem];
        [contact retain];
        [contact setTitle:@"Add Contact" forState:UIControlStateNormal];
        [contact addTarget:self action:@selector(addContact:) forControlEvents:UIControlEventTouchDown];
        contact.titleLabel.font = [UIFont systemFontOfSize: 10*rapport];
        
        forget = [UIButton buttonWithType:UIButtonTypeSystem];
        [forget retain];
        [forget setTitle:@"Forget" forState:UIControlStateNormal];
        [forget addTarget:self action:@selector(removePin:) forControlEvents:UIControlEventTouchDown];
        forget.titleLabel.font = [UIFont systemFontOfSize: 10*rapport];
        
        remember = [UIButton buttonWithType:UIButtonTypeSystem];
        [remember retain];
        [remember setTitle:@"Remember" forState:UIControlStateNormal];
        [remember addTarget:self action:@selector(savePin:) forControlEvents:UIControlEventTouchDown];
        remember.titleLabel.font = [UIFont systemFontOfSize: 10*rapport];
       
        [self addSubview:contact];
        [self addSubview:remember];
        [self addSubview:forget];
        
        abNavCont = [[ABPeoplePickerNavigationController alloc] init];
        [abNavCont setPeoplePickerDelegate:self];
        [abNavCont retain];
        
        currentPoint = [MKPointAnnotation alloc];
        [currentPoint retain];
        
        if ([CLLocationManager locationServicesEnabled]) {
            map = [[MKMapView alloc] init];
            [map setScrollEnabled:YES];
            [map setZoomEnabled:YES];
            [self addSubview:map];
            [map setDelegate:self];
            
            MKCoordinateRegion region;
            region.center.longitude = 2.3548;
            region.center.latitude = 48.8464;
            region.span.longitudeDelta = 0.109863;
            region.span.latitudeDelta = 0.112872;
            
            [map setRegion:region animated:YES];
            
            locManager = [[CLLocationManager alloc] init];
            [locManager setDistanceFilter:1.0];
            [locManager setDelegate:self];
            [locManager retain];
        } else {
            UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"Erreur" message:@"Localisation désactivée" delegate:nil cancelButtonTitle:@"OK" otherButtonTitles:nil];
            [alert show];
            [alert release];
        }
        nbLieu = 1;
    }
    return self;
}

/*
// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect
{
    // Drawing code
}
*/


-(void) setFromOrientation:(UIInterfaceOrientation) o {
    if (o == UIInterfaceOrientationLandscapeLeft || o == UIInterfaceOrientationLandscapeRight) {
        heigth = myframe.size.width;
        width = myframe.size.height;
    } else {
        width = myframe.size.width;
        heigth = myframe.size.height;
    }
    [remember setFrame:CGRectMake(width/2-60, y_origin+5, 120, 20*rapport)];
    [map setFrame:CGRectMake(x_origin, 3*y_origin+40*rapport, width -2*x_origin, heigth - (4*y_origin + 40*rapport))];
    [forget setFrame:CGRectMake(width-80, y_origin+5, 80, 20)];
    [contact setFrame:CGRectMake(width/2-75, 2*y_origin+20*rapport, 150, 20*rapport)];
}


- (void)mapView:(MKMapView *)mapView didUpdateUserLocation:(MKUserLocation *)userLocation {
    MKCoordinateRegion region;
    MKCoordinateSpan span;
    span.latitudeDelta = 0.005;
    span.longitudeDelta = 0.005;
    CLLocationCoordinate2D location;
    location.latitude = userLocation.coordinate.latitude;
    location.longitude = userLocation.coordinate.longitude;
    region.span = span;
    region.center = location;
    [mapView setRegion:region animated:YES];
}


-(void) removePin:(id)sender{
    NSArray *arrayAnnot = [map selectedAnnotations];
    [arrayAnnot retain];
    if ([arrayAnnot count] != 0 ) {
        currentPoint = [arrayAnnot objectAtIndex:0];
        [map removeAnnotation:currentPoint];
    } else {
        UIAlertView *tmp = [[UIAlertView alloc] initWithTitle:@"Error" message:@"You didn't select any pin" delegate:nil cancelButtonTitle:@"OK" otherButtonTitles:nil];
        [tmp autorelease];
        [tmp show];
    }
}

-(void) savePin:(id)sender{
    MKPointAnnotation *newPtAnnot = [[MKPointAnnotation alloc] init];
    [newPtAnnot setTitle:[NSString stringWithFormat:@"Lieu %d", nbLieu++]];
    [newPtAnnot setCoordinate:[map centerCoordinate]];
    [map addAnnotation:newPtAnnot];
    [newPtAnnot release];
}

-(void) addContact:(id)sender{
    NSArray *annotTab = [map selectedAnnotations];
    [annotTab retain];
    if ([annotTab count] == 0 ) {
        UIAlertView *tmp = [[UIAlertView alloc] initWithTitle:@"Error" message:@"You didn't select any pin" delegate:nil cancelButtonTitle:@"OK" otherButtonTitles:nil];
        [tmp autorelease];
        [tmp show];
    } else {
        [abNavCont setPeoplePickerDelegate:self];
        NSArray *aAfficher = [NSArray arrayWithObjects:[NSNumber numberWithInt:kABPersonPhoneProperty],nil];
        [aAfficher retain];
        [abNavCont setDisplayedProperties:aAfficher];
        [self.myViewCont presentViewController:abNavCont animated:YES completion:nil];
        currentPoint = [annotTab objectAtIndex:0];
    }
}

-(BOOL) peoplePickerNavigationController:(ABPeoplePickerNavigationController *)p shouldContinueAfterSelectingPerson:(ABRecordRef)person{
    NSString *tmpName = (NSString *)ABRecordCopyValue(person, kABPersonFirstNameProperty);
    if ([tmpName isEqual:nil]) {
        tmpName=@"";
    }
    NSString *firstName = [tmpName stringByAppendingString:@" "];
    NSString *lastName = (NSString *)ABRecordCopyValue(person, kABPersonLastNameProperty);
    if (lastName == nil) {
        lastName = @"";
    }
    if (firstName == nil) {
        firstName = @"";
    }
    NSString *finalName = [firstName stringByAppendingString:lastName];
    [currentPoint setSubtitle: finalName];
    [self.myViewCont dismissViewControllerAnimated:YES completion:nil];
    return NO;
}

-(void) peoplePickerNavigationControllerDidCancel:(ABPeoplePickerNavigationController *)peoplePicker{
    [self.myViewCont dismissViewControllerAnimated:YES completion:nil];
}


-(void) newPersonViewController:(ABNewPersonViewController *)newPersonView didCompleteWithNewPerson:(ABRecordRef)person{
    [self.myViewCont dismissViewControllerAnimated:YES completion:nil];
}


-(BOOL) peoplePickerNavigationController:(ABPeoplePickerNavigationController *)peoplePicker shouldContinueAfterSelectingPerson:(ABRecordRef)person property:(ABPropertyID)property identifier:(ABMultiValueIdentifier)identifier{
    return NO;
}

-(void) dealloc{
    [abNavCont release];
    [abNewPersCont release];
    [self.myViewCont release];
    [currentPoint release];
    [map release];
    [super dealloc];
}


@end
