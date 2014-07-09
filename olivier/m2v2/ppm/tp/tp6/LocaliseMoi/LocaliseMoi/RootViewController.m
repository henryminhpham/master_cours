//
//  RootViewController.m
//  LocaliseMoi
//
//  Created by m2sar on 10/01/2014.
//  Copyright (c) 2014 m2sar. All rights reserved.
//

#import "RootViewController.h"

@interface RootViewController ()

@end

@implementation RootViewController

- (id)initWithStyle:(UITableViewStyle)style
{
    self = [super initWithStyle:style];
    if (self) {
        [self setTitle:@"Historique"];
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(receiveEvent::) name:@"LocaliseMoi" object:nil];
        NSArray *d = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
        path = [[d objectAtIndex:0] stringByAppendingPathComponent:@"historique"];
        [path retain];
        historique = [[self loadHistorique] retain];
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    [self loadHistorique];
    UIBarButtonItem *savebt = [[UIBarButtonItem alloc]
                               initWithBarButtonSystemItem:UIBarButtonSystemItemSave target:self action:@selector(persistHistorique)];
    [[self navigationItem] setRightBarButtonItem:savebt];
    [[self navigationItem] setLeftBarButtonItem:[self editButtonItem]];
    [savebt release];
}

- (void) receiveEvent:(id) sender :(NSDictionary*) userInfo {
    [historique insertObject:[_mapView getMapContent] atIndex:0];
    [[self tableView] reloadData];
}

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return [historique count];
}


-(void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath{
    CellMapContent* mapContent = [historique objectAtIndex:[indexPath row]];
    [_mapView makePosition:mapContent];
}

- (UITableViewCell*) tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    static NSString *CellIdentifier = @"MapCell";
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
    if(cell == nil) {
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleValue1 reuseIdentifier:CellIdentifier];
    }
    CellMapContent* mapContent = [historique objectAtIndex:[indexPath row]];
    [[cell textLabel] setText:[mapContent label]];
    return cell;
}

-(void) persistHistorique {
    NSLog(@"Enregistrement de %d données.", [historique count]);
    [NSKeyedArchiver archiveRootObject:historique toFile:path];
}

-(NSMutableArray*) loadHistorique {
    return [NSKeyedUnarchiver unarchiveObjectWithFile:path];
}


- (void)tableView:(UITableView *)tableView commitEditingStyle:(UITableViewCellEditingStyle)editingStyle forRowAtIndexPath:(NSIndexPath *)indexPath
{
    if (editingStyle == UITableViewCellEditingStyleDelete) {
        // Delete the row from the data source
        [historique removeObjectAtIndex:[indexPath row]];
        [tableView deleteRowsAtIndexPaths:@[indexPath] withRowAnimation:UITableViewRowAnimationFade];
    }
    else if (editingStyle == UITableViewCellEditingStyleInsert) {
        // Create a new instance of the appropriate class, insert it into the array, and add a new row to the table view
    }
}

- (void) splitViewController:(UISplitViewController *)svc willHideViewController:(UIViewController *)aViewController withBarButtonItem:(UIBarButtonItem *)barButtonItem forPopoverController:(UIPopoverController *)pc {
    [barButtonItem setTitle:@"Mes Localisations"];
    [_mapView showNavigationButton:barButtonItem];
}

-(void) splitViewController:(UISplitViewController *)svc willShowViewController:(UIViewController *)aViewController invalidatingBarButtonItem:(UIBarButtonItem *)barButtonItem {
    [_mapView hideNavigationButton];
}


-(void)viewWillAppear:(BOOL)animated{
    [[self tableView] reloadData];
}

-(BOOL)tableView:(UITableView *)tableView canEditRowAtIndexPath:(NSIndexPath *)indexPath{
    return YES;
}
-(BOOL)tableView:(UITableView *)tableView canMoveRowAtIndexPath:(NSIndexPath *)indexPath{
    return YES;
}

- (void)tableView:(UITableView *)tableView moveRowAtIndexPath:(NSIndexPath *)fromIndexPath toIndexPath:(NSIndexPath *)toIndexPath
{
    CellMapContent *tmp = [historique objectAtIndex:[fromIndexPath row]];
    [historique removeObjectAtIndex:[fromIndexPath row]];
    [historique insertObject:tmp atIndex:[toIndexPath row]];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
}

- (void) dealloc {
    [[NSNotificationCenter defaultCenter] removeObserver:self];
    [path release];
    path = nil;
    [historique release];
    historique = nil;
    [super dealloc];
}

@end
