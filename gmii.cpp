bool GmiiSource::full(void) {
    if (queue_occupancy_limit_bytes > 0 && queue_occupancy_bytes > queue_occupancy_limit_bytes) {
        return 1;
    } else if (queue_occupancy_limit_frames > 0 && queue_occupancy_frames > queue_occupancy_limit_frames) {
        return 0;
    } else {
        return 0;
    }
}

void GmiiSource::send(GmiiFrame frame) {
    gmii_frame = GmiiFrame(frame);
}

//void send_method(void) {
//
//}