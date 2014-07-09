//
//  MoodControllerViewController.m
//  iMoods
//
//  Created by m2sar on 12/01/2014.
//  Copyright (c) 2014 m2sar. All rights reserved.
//

#import "MyTableViewController.h"

@interface MyTableViewController ()

@end

@implementation MyTableViewController

- (id)initWithStyle:(UITableViewStyle)style
{
    self = [super initWithStyle:style];
    if (self) {
        voisins = [[NSMutableArray alloc] init];
        [[self navigationItem] setTitle:@"iMoods"];
        UIBarButtonItem *edit = [[UIBarButtonItem alloc] initWithTitle:@"Edit" style:UIBarButtonItemStyleDone target:self action:@selector(navigate)];
        [[self navigationItem] setRightBarButtonItem:edit];
        
        currentMood = @"Happy";
        
        center = [NSNotificationCenter defaultCenter];
        [center addObserver:self selector:@selector(onChangeMood:) name:@"mood" object:nil];
        
        
        find = [[NSNetService alloc] initWithDomain:@"local" type:@"_moods._tcp" name:[self getPreferencesName] port:9090];
        [find setDelegate:self];
        [find setIncludesPeerToPeer:YES];
        [find startMonitoring];
        [find publish];
        
        findBrowser = [[NSNetServiceBrowser alloc] init];
        [findBrowser setDelegate:self];
        [findBrowser searchForServicesOfType:@"_moods._tcp" inDomain:@"local"];
    }
    return self;
}

- (NSString*) getPreferencesName {
    NSString* name = [[UIDevice currentDevice] name];
    if(name == nil) {
        name = @"Sans nom";
    }
    return name;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    [[self tableView] reloadData];
}

- (void) onChangeMood: (NSNotification*) notification {
    NSDictionary* dict = [notification userInfo];
    currentMood = [dict valueForKey:@"mood"];
    [self publish];
}

- (void) publish {
    NSDictionary* dico = [NSDictionary dictionaryWithObject:[currentMood dataUsingEncoding:NSUTF8StringEncoding] forKey:@"mood"];
    [find setTXTRecordData:[NSNetService dataFromTXTRecordDictionary:dico]];
    
}

- (void) netService:(NSNetService *)service didUpdateTXTRecordData:(NSData *)data {
    if(!data) {
        NSLog(@"Impossible de récupérer les données du service %@", [service name]);
        return;
    }
    NSData* mData = [[NSNetService dictionaryFromTXTRecordData:data] objectForKey:@"mood"];
    if(!mData) {
        NSLog(@"Impossible de récupérer les données transformées du service %@", [service name]);
        return;
    }
    for(NSUInteger i = 0 ; i < [voisins count] ; i++) {
        MyCell* cell = [voisins objectAtIndex:i];
        if([[cell label] compare:[service name]] == NSOrderedSame) {
            NSString* mood = [[NSString alloc] initWithData:mData encoding:NSUTF8StringEncoding];
            NSLog(@"Mise à jour de l'humeur de %@. Il est %@", [service name], mood);
            [cell setDetail:mood];
            [[self tableView] reloadData];
            return;
        }
    }
}

- (void) netServiceBrowser:(NSNetServiceBrowser *)aNetServiceBrowser didFindService:(NSNetService *)service moreComing:(BOOL)moreComing {
    if(![service isEqual:find]) {
        [service startMonitoring];
        [service setDelegate:self];
        [service retain];
    }
    [services addObject:service];
    NSData* data = [service TXTRecordData];
    if(!data) {
        [voisins addObject:[[MyCell alloc] initWithLabel:[service name] andWithDetail:@"Inconnu"]];
        [[self tableView] reloadData];
        NSLog(@"Ajout de %@ dans l'humeur Inconnu", [service name]);
        [self publish];
        return;
    }
    NSData* mData = [[NSNetService dictionaryFromTXTRecordData:data] objectForKey:@"mood"];
    if(!mData) {
        [voisins addObject:[[MyCell alloc] initWithLabel:[service name] andWithDetail:@"Inconnu"]];
        [[self tableView] reloadData];
        NSLog(@"Ajout de %@ dans l'humeur Inconnu", [service name]);
        [self publish];
        return;
    }
    NSString* mood = [[NSString alloc] initWithData:mData encoding:NSUTF8StringEncoding];
    [voisins addObject:[[MyCell alloc] initWithLabel:[service name] andWithDetail:mood]];
    [[self tableView] reloadData];
    NSLog(@"Ajout de %@ dans l'humeur %@", [service name], mood);
    [self publish];
    
}

- (void) netServiceBrowser:(NSNetServiceBrowser *)aNetServiceBrowser didRemoveService:(NSNetService *)service moreComing:(BOOL)moreComing {
    for(NSUInteger i = 0 ; i < [voisins count] ; i++) {
        MyCell* cell = [voisins objectAtIndex:i];
        if([[cell label] compare:[service name]] == NSOrderedSame) {
            [voisins removeObject:cell];
            [[self tableView] reloadData];
            NSLog(@"Suppression de %@", [service name]);
            return;
        }
    }
}

- (void) netService:(NSNetService *)sender didNotPublish:(NSDictionary *)errorDict {
    [find stopMonitoring];
    [find stop];
    [find release];
    [findBrowser stop];
    [findBrowser release];
}

- (void) navigate {
    SecondViewController *vc = [[SecondViewController alloc] initWithNibName:[super nibName] bundle:[super nibBundle]];
    [[self navigationController] pushViewController:vc animated:YES];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
}

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return [voisins count];
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    static NSString *CellIdentifier = @"Cell";
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
    
    if (cell==nil) {
        cell = [[UITableViewCell alloc]  initWithStyle:UITableViewCellStyleSubtitle reuseIdentifier:CellIdentifier];
        [cell retain];
    }
    MyCell* myCell = [voisins  objectAtIndex:[indexPath row]];
    [[cell textLabel] setText:[NSString stringWithFormat:@"%@",[myCell label]]];
    [[cell detailTextLabel] setText:[NSString stringWithFormat:@"%@",[myCell detail]]];
    
    if ([[myCell detail]  isEqual: @"Happy"]) {
        [[cell detailTextLabel] setTextColor:[UIColor greenColor]];
    } else if ([[myCell detail]  isEqual: @"Sad"]) {
            [[cell detailTextLabel] setTextColor:[UIColor grayColor]];
    } else if ([[myCell detail]  isEqual: @"Angry"]){
            [[cell detailTextLabel] setTextColor:[UIColor redColor]];
    } else {
            [[cell detailTextLabel] setTextColor:[UIColor blueColor]];
    }
    return cell;
}

- (void) dealloc {
    [find stopMonitoring];
    [find release];
    [findBrowser stop];
    [findBrowser release];
    [center removeObserver:self];
    center = nil;
    [voisins release];
    for(NSUInteger i = 0 ; i < [services count] ; i++) {
        NSNetService* service = [services objectAtIndex:i];
        [service stopMonitoring];
        [service stop];
        [service release];
    }
    [services release];
    [super dealloc];
}

/*
// Override to support conditional editing of the table view.
- (BOOL)tableView:(UITableView *)tableView canEditRowAtIndexPath:(NSIndexPath *)indexPath
{
    // Return NO if you do not want the specified item to be editable.
    return YES;
}
*/

/*
// Override to support editing the table view.
- (void)tableView:(UITableView *)tableView commitEditingStyle:(UITableViewCellEditingStyle)editingStyle forRowAtIndexPath:(NSIndexPath *)indexPath
{
    if (editingStyle == UITableViewCellEditingStyleDelete) {
        // Delete the row from the data source
        [tableView deleteRowsAtIndexPaths:@[indexPath] withRowAnimation:UITableViewRowAnimationFade];
    }   
    else if (editingStyle == UITableViewCellEditingStyleInsert) {
        // Create a new instance of the appropriate class, insert it into the array, and add a new row to the table view
    }   
}
*/

/*
// Override to support rearranging the table view.
- (void)tableView:(UITableView *)tableView moveRowAtIndexPath:(NSIndexPath *)fromIndexPath toIndexPath:(NSIndexPath *)toIndexPath
{
}
*/

/*
// Override to support conditional rearranging of the table view.
- (BOOL)tableView:(UITableView *)tableView canMoveRowAtIndexPath:(NSIndexPath *)indexPath
{
    // Return NO if you do not want the item to be re-orderable.
    return YES;
}
*/

/*
#pragma mark - Navigation

// In a story board-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender
{
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}

 */

@end
